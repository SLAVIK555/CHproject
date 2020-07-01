#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <iostream>

//using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // while (true){
    std::vector<int>p = {4, 5, 7, 2, 1};
    std::vector<float>t = {0, 1, 2, 3, 4};
    std::cout << "jfoijfewijoewf" << endl;
    //drawgraph(p, t);
    //sleep(1);
    //}
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawgraph(std::vector<int> parameter, std::vector<float> apprtime)
{
    QLineSeries *series = new QLineSeries();

    //std::vector<int>::iterator it=parameter.begin();
    for(int it=0; it<parameter.size(); it++){
        series->append(apprtime[it], parameter[it]);//x - apprtime, y - parameter
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Paraneter and appropriate time");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);

}
