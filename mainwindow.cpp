#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>
#include<tablettestview.h>
#include "point.h"
#include "alphabet.h"
#include "stride.h"

#include <QTabletEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusBar()->showMessage(tr("Hello"));

    QGraphicsScene *pScene=new QGraphicsScene;

    connect(ui->tabletView, SIGNAL(newStrideEvent(const QTabletEvent*)), this, SLOT(showStrides(const QTabletEvent*)));
    connect(ui->tabletView, SIGNAL(newPointEvent(const QTabletEvent*)), this, SLOT(showPoints(const QTabletEvent*)));


    Point point(34, 32, 0.3);
    Point point1( QPoint(34, 32), 0.333);

    statusBar()->showMessage(QString::number(point.y()));

    stride1.append(point);
    stride1.append(point1);

    Alphabet alpha;
    alpha.append(stride1);
    alpha.append(stride1);

//    for(int i = 0; i < alpha.size(); ++i) {
//        qDebug() << alpha.at(i).size();
//    }
    alpha.last().append(point);
    qDebug() << alpha.last().last().getPressure();
//    alpha.addNewStride();
//    alpha.currentStride->points.append(point);
//    alpha.addNewStride();
//    alpha.currentStride->addPoint(point1);

//    for(int i = 0; i < alpha.strides.size(); ++i) {
//        qDebug() << "Stride at " << QString::number(i) << " " << alpha.strides.at(i).points.size();
//        for(int j = 0; j < alpha.strides.at(i).points.size(); ++j) {
//            qDebug() << "Point " << j << " of Stride " << i;
//            qDebug() << QString::number(alpha.strides.at(i).points.at(j).getPressure());
//        }
//    }

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
