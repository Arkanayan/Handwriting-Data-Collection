#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>
#include<tablettestview.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusBar()->showMessage(tr("Hello"));

    QGraphicsScene *pScene=new QGraphicsScene;

}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {

    qDebug() << "Mouse move event";
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    qDebug() << "Mouse press event";

}

MainWindow::~MainWindow()
{
    delete ui;
}
