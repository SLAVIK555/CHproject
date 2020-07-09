#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

#include <QtSql>
#include <QString>

#include <iostream>
#include <vector>
#include <unistd.h>

#include "clickhouse/client.h"

#include "fvnpclass.h"

using namespace std;
using namespace clickhouse;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public FVNPclass
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::vector<int>p;//={1, 2, 3};//по этим данным строятся графики
    std::vector<float>t;//={1, 2, 3};

    std::vector<int>TOid;//сюда записываются параметры с датчика
    std::vector<float>TOname;

    int time = 0;

    //int classintrand(int min, int max);
    void QCPdrowgraph(std::vector<int>p, std::vector<float>t);


private:
    Ui::MainWindow *ui;
    QTimer *tmr;
    QTimer *tot;

private slots:
    //void tableObserver();
    void updateGraph();
    void pushButton_clicked(Client &client);
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
