#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    //QCPdrowgraph(p, t);

    tot = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    tot->setInterval(800); // Задаем интервал таймера
    connect(tot, SIGNAL(timeout()), this, SLOT(tableObserver())); // Подключаем сигнал таймера к нашему слоту
    cout << "success tot" << endl;
    tot->start(); // Запускаем таймер

    tmr = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    tmr->setInterval(100); // Задаем интервал таймера
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateGraph())); // Подключаем сигнал таймера к нашему слоту
    cout << "success tmr" << endl;
    tmr->start(); // Запускаем таймер
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::classintrand(int min, int max){
    static const double fraction = 1.0/(static_cast<double>(RAND_MAX)+1.0);
    return static_cast<int>(rand()*fraction*(max-min+1)*min);
}

void MainWindow::QCPdrowgraph(std::vector<int> p, std::vector<float> t){

       QVector<double> x, y; //Массивы координат точек

       //Вычисляем наши данные
       for (size_t i=0; i<p.size(); i++)//Пробегаем по всем точкам
       {
           //cout <<"success" << endl;
           x.push_back(t[i]);
           y.push_back(p[i]);//Формула нашей функции
       }

       ui->widget->clearGraphs();//Если нужно, но очищаем все графики
       //Добавляем один график в widget
       ui->widget->addGraph();
       //Говорим, что отрисовать нужно график по нашим двум массивам x и y
       ui->widget->graph(0)->setData(x, y);

       //Подписываем оси Ox и Oy
       //ui->widget->xAxis->setLabel("t");
       //ui->widget->yAxis->setLabel("p");
       //Установим область, которая будет показываться на графике
       double minX = x[0], maxX = x[0];
       for (size_t i=1; i<t.size(); i++)
       {
           if (x[i]<minX) minX = x[i];
           if (x[i]>maxX) maxX = x[i];
       }

       //Для показа границ по оси Oy сложнее, так как надо по правильному
       //вычислить минимальное и максимальное значение в векторах
       double minY = y[0], maxY = y[0];
       for (size_t i=1; i<p.size(); i++)
       {
           if (y[i]<minY) minY = y[i];
           if (y[i]>maxY) maxY = y[i];
       }

       ui->widget->xAxis->setRange(minX, maxX);//Для оси Ox
       ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

       //И перерисуем график на нашем widget
       ui->widget->replot();
}

void MainWindow::tableObserver(){
    //tmr->stop();
    std::cout << "Start table observer" << endl;
    //p.push_back(classintrand(1, 10));
    //t.push_back(time);
    //time++;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    db.setDatabaseName("mysql_db");
    db.setUserName("");
    db.setPassword("");
    bool connected = db.open();

    if(!connected){
        cout << "connect fail" << endl;
        //return 1;
    }

    QSqlQueryModel model;
    model.setQuery("select * from test.numbers");

    TOid.clear();
    TOname.clear();

    for (int i = 0; i < model.rowCount(); ++i){
        QSqlRecord record = model.record(i);

        TOid.push_back(record.value("id").toInt());
        TOname.push_back(record.value("name").toFloat());
        //Тут должен вызываться отрисовщик графика раз в 0.25 сек
        //W.drawgraph(TOid, TOname);
    }
    //return 0;
    std::cout << "End table observer" << endl;
    //tmr->start();
}

void MainWindow::updateGraph(){
    //tot->stop();
    //ui->label->setText(QTime::currentTime().toString()); // Обновляем время на экране
    std::cout << "Start ploting graph" << endl;
    //std::cout << TOid[1] << endl;

    if(!TOid.empty() && !TOname.empty()){
        for(int i=0; i<TOid.size(); i++){
            p.push_back(TOid[i]);
            t.push_back(TOname[i]);
        }
    }

    QVector<double> x, y; //Массивы координат точек

    //Вычисляем наши данные
    if(!p.empty() && !t.empty()){
    for (size_t i=0; i<p.size(); i++)//Пробегаем по всем точкам
    {
        //cout <<"success" << endl;
        x.push_back(t[i]);
        y.push_back(p[i]);//Формула нашей функции
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);
    //Подписываем оси Ox и Oy
    //ui->widget->xAxis->setLabel("t");
    //ui->widget->yAxis->setLabel("p");
    //Установим область, которая будет показываться на графике
    double minX = x[0], maxX = x[0];
    for (size_t i=1; i<t.size(); i++)
    {
        if (x[i]<minX) minX = x[i];
        if (x[i]>maxX) maxX = x[i];
    }

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    double minY = y[0], maxY = y[0];
    for (size_t i=1; i<p.size(); i++)
    {
        if (y[i]<minY) minY = y[i];
        if (y[i]>maxY) maxY = y[i];
    }

    ui->widget->xAxis->setRange(minX, maxX);//Для оси Ox
    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    //И перерисуем график на нашем widget
    ui->widget->replot();
    }
    std::cout << "End ploting graph" << endl;
    //tot->start();
}
