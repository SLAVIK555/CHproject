#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSql>

#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QtCharts/QLineSeries>

#include <iostream>
#include <vector>

#include <thread>

#include <unistd.h>
#include "clickhouse/client.h"

using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawgraph(std::vector<int>parameter, std::vector<float>apprtime);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
