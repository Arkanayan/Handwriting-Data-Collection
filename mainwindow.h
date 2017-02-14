#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stride.h"
#include <QTabletEvent>
#include "alphabet.h"
#include "dbmanager.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     Stride stride1;

private:
    Ui::MainWindow *ui;
    Alphabet alphabet;
    DbManager *db;

public slots:
    void showStrides(const QTabletEvent *);
    void showPoints(const QTabletEvent *);
    void showData();

private slots:
    void on_showData_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
