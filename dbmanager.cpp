#include "dbmanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QVariantList>

DbManager::DbManager()
{

}

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok\n" << path;
    }
}


bool DbManager::createDb() {

    bool success = false;

    QString path = "handwriting.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query;

    if(query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id integer PRIMARY KEY AUTOINCREMENT,"
                    "first_name varchar,"
                    "last_name varchar,"
                    "age integer,"
                    "gender varchar,"
                    "school varchar,"
                    "competency varchar,"
                    "extra_info text"
                     ");")) {

        qDebug() << "Users table creation successfull";
        success = true;

    } else {
        qDebug() << "Users Table creation failed:  "
                       << query.lastError();
    }

    if(query.exec(  "CREATE TABLE IF NOT EXISTS sample_texts ("
                    "id integer PRIMARY KEY AUTOINCREMENT,"
                    "name varchar,"
                    "text text,"
                    "image blob"
                    ");")) {

        qDebug() << "sample_texts table creation successfull";
        success = true;

    } else {
        qDebug() << "sample_texts Table creation failed:  "
                       << query.lastError();
    }

    if(query.exec(  "CREATE TABLE IF NOT EXISTS points ("
                      "id integer PRIMARY KEY AUTOINCREMENT,"
                      "position integer,"
                      "x integer,"
                      "y integer,"
                      "pressure real,"
                      "stride_id integer"
                       ");")) {

        qDebug() << "points table creation successfull";
        success = true;

    } else {
        qDebug() << "points Table creation failed:  "
                       << query.lastError();
    }

    if(query.exec(  "CREATE TABLE IF NOT EXISTS strides ("
                      "id integer PRIMARY KEY AUTOINCREMENT,"
                      "sample_text_id integer,"
                      "alphabet_id integer"
                        ");")) {

        qDebug() << "strides table creation successfull";
        success = true;

    } else {
        qDebug() << "strides Table creation failed:  "
                       << query.lastError();
    }

    if(query.exec(
                "CREATE TABLE IF NOT EXISTS alphabets ("
                    "id integer PRIMARY KEY AUTOINCREMENT,"
                    "user_id integer,"
                    "sample_text_id integer,"
                    "date_created timestamp DEFAULT CURRENT_TIMESTAMP"
                ");"
        )) {

        qDebug() << "alphabets table creation successfull";
        success = true;

    } else {
        qDebug() << "alphabets Table creation failed:  "
                       << query.lastError();
    }


    return success;
}

bool DbManager::insertPoint(const Point &point,const int position, const int stride_id)
{
    bool success = false;

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO points(position, x, y, pressure, stride_id) VALUES(:position, :x, :y, :pressure, :stride_id)");
    query.bindValue(":position", position);
    query.bindValue(":x", point.x());
    query.bindValue(":y", point.y());
    query.bindValue(":pressure", point.getPressure());
    query.bindValue(":stride_id", stride_id);


    if(query.exec()) {
        success = true;
    } else {
        qDebug() << "Point insertion error:  "
                       << query.lastError();

        success = false;
    }

    return success;
}

bool DbManager::insertAlphabet(const Alphabet &alphabet, const int user_id, const int sample_text_id) {

    bool success = true;

    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();

    QSqlQuery query;
    query.prepare("INSERT INTO alphabets(user_id, sample_text_id) VALUES(?, ?)");
    query.addBindValue(user_id);
    query.addBindValue(sample_text_id);

    if(query.exec()) {
        qDebug() << "Alphabet inserted: " << query.lastInsertId().toInt();
    } else {
        qDebug() << "Alphabet inserted falied";
        db.rollback();
        return false;
    }
    int lastInsertedAlphabetId = query.lastInsertId().toInt();

    for(int i = 0; i < alphabet.size(); ++i) {
        if(!insertStride(alphabet.at(i), lastInsertedAlphabetId, sample_text_id)) {
            db.rollback();
            return false;
        }
    }

    db.commit();


    return success;
}

bool DbManager::insertStride(const Stride &stride, const int alphabet_id, const int sample_text_id) {

    if (stride.size() == 0) {
        qDebug() << "Stride is empty.";
        return false;
    }

    bool success = false;

    QVariantList position, x, y, pressure, stride_id;

    int insertedStrideId = 325;

    QSqlQuery query;

    // For sqlite speed
    query.exec("PRAGMA synchronous = OFF");
    query.exec("PRAGMA journal_mode = MEMORY");

    query.exec("INSERT INTO strides(sample_text_id, alphabet_id) VALUES(?, ?)");
    query.addBindValue(sample_text_id);
    query.addBindValue(alphabet_id);

    if(!query.exec()) {
        qDebug() << "Stride insertion failed";
        return false;
    }

    insertedStrideId = query.lastInsertId().toInt();

    for(int i = 0; i < stride.size(); ++i) {

       position << i;
       x << stride.at(i).x();
       y << stride.at(i).y();
       pressure << stride.at(i).getPressure();
       stride_id << insertedStrideId;
    }

    query.prepare("INSERT INTO points(position, x, y, pressure, stride_id) VALUES(:position, :x, :y, :pressure, :stride_id)");
    query.bindValue(":position", position);
    query.bindValue(":x", x);
    query.bindValue(":y", y);
    query.bindValue(":pressure", pressure);
    query.bindValue(":stride_id", stride_id);

    if(query.execBatch()) {
        success = true;
        qDebug() << "Stride Inserted";

    } else {
        qDebug() << "Stride insertion error:  "
                       << query.lastError();

        success = false;
    }

    return success;
}

