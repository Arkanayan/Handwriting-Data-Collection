#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include "alphabet.h"
#include "point.h"
#include "stride.h"

class DbManager
{
public:
    DbManager();
    DbManager(const QString &path);
    bool insertPoint(const Point &point, const int position, const int stride_id);
    bool insertStride(const Stride &stride, const int alphabet_id, const int sample_text_id);
    bool createDb();
    bool insertAlphabet(const Alphabet &alphabet, const int user_id = 0 , const int sample_text_id = 0);
private:
   QSqlDatabase m_db;
};

#endif // DBMANAGER_H
