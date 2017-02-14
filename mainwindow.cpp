#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>
#include<tablettestview.h>
#include "point.h"
#include "alphabet.h"
#include "stride.h"

#include <QStandardPaths>
#include <QTabletEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

  //  db = new DbManager(QStandardPaths::locate(QStandardPaths::HomeLocation, "hand.db"));
    db = new DbManager();

    db->createDb();

    statusBar()->showMessage(tr("Hello"));

    QGraphicsScene *pScene=new QGraphicsScene;

    connect(ui->tabletView, SIGNAL(newStrideEvent(const QTabletEvent*)), this, SLOT(showStrides(const QTabletEvent*)));
    connect(ui->tabletView, SIGNAL(newPointEvent(const QTabletEvent*)), this, SLOT(showPoints(const QTabletEvent*)));


    _eventlog = new EventLogDialog(this);

    connect(ui->tabletView, SIGNAL(logEvent(QString)), _eventlog, SLOT(logEvent(QString)));

    connect(ui->eventLogAction, SIGNAL(triggered(bool)), _eventlog, SLOT(show()));

}

void MainWindow::showStrides(const QTabletEvent* event) {

    Stride stride;
    Point point(event->x(),event->y(), event->pressure());
    stride.append(point);
    alphabet.append(stride);

    qDebug() << QString("Stride: x: %1  y: %2 p: %3").arg(event->x()).arg(event->y()).arg(event->pressure());
}

void MainWindow::showPoints(const QTabletEvent* event) {
    Point point(event->x(),event->y(), event->pressure());
    alphabet.last().append(point);
    qDebug() << QString("Point: x: %1  y: %2 p: %3").arg(event->x()).arg(event->y()).arg(event->pressure());

}

void MainWindow::showData() {
    qDebug() << "Showing data\n";
    for(int strides = 0; strides < alphabet.size(); ++strides) {
        for(int points = 0; points < alphabet.at(strides).size(); ++points) {
            Point point = alphabet.at(strides).at(points);
            qDebug() << QString("Stride: %1 , Point: %2 %3 %4").arg(strides).arg(point.x()).arg(point.y()).arg(point.getPressure());
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_showData_clicked()
{
    showData();
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Last stride size: " << alphabet.last().size();
    //db->insertStride(alphabet.last(), 324);
    db->insertAlphabet(alphabet);
//    for(int i = 0; i < alphabet.last().size(); i++) {
//        Point tempPoint = alphabet.last().at(i);
//        db->insertPoint(tempPoint, i, alphabet.size() - 1);
//    }
}
