#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clickhouse/client.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //std::cout << fvnp_par << endl;
    //QCPdrowgraph(p, t);

    /*tot = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    tot->setInterval(800); // Задаем интервал таймера
    connect(tot, SIGNAL(timeout()), this, SLOT(tableObserver())); // Подключаем сигнал таймера к нашему слоту
    cout << "success tot" << endl;
    tot->start(); // Запускаем таймер*/

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

/*int MainWindow::classintrand(int min, int max){
    static const double fraction = 1.0/(static_cast<double>(RAND_MAX)+1.0);
    return static_cast<int>(rand()*fraction*(max-min+1)*min);
}*/

/*void MainWindow::QCPdrowgraph(std::vector<int> p, std::vector<float> t){

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
}*/

/*void MainWindow::tableObserver(){
    //tmr->stop();
    //std::cout << "Start table observer" << endl;
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
    //std::cout << "End table observer" << endl;
    //tmr->start();
}*/

void MainWindow::updateGraph(){
    FVNPclass F;
    //table observing
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    //db.setDatabaseName("mysql_db");
    db.setUserName("");
    db.setPassword("12345678");
    bool connected = db.open();

    if(!connected){
        cout << "connect fail" << endl;
        //return 1;
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики


    QSqlQueryModel model;

    for (int i=0; i<fvnp_num+1; i++){
    string str = "select * from num_" + F.too_string(i);
    const QString Q = QString::fromStdString(str);
    model.setQuery(Q);

    p.clear();
    t.clear();

    for (int i = 0; i < model.rowCount(); ++i){
        QSqlRecord record = model.record(i);

        p.push_back(record.value("param").toInt());
        t.push_back(record.value("ptime").toFloat());
    }
    //tot->stop();
    //ui->label->setText(QTime::currentTime().toString()); // Обновляем время на экране
    //std::cout << "Start ploting graph" << endl;
    //std::cout << TOid[1] << endl;

    /*if(!TOid.empty() && !TOname.empty()){
        for(int i=0; i<TOid.size(); i++){
            p.push_back(TOid[i]);
            t.push_back(TOname[i]);
        }
    }*/

    QVector<double> x, y; //Массивы координат точек

    //Вычисляем наши данные
    if(!p.empty() && !t.empty()){
    for (size_t i=0; i<p.size(); i++)//Пробегаем по всем точкам
    {
        //cout <<"success" << endl;
        x.push_back(t[i]);
        y.push_back(p[i]);//Формула нашей функции
    }

    //ui->widget->clearGraphs();//Если нужно, но очищаем все графики
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
    //std::cout << "End ploting graph" << endl;
    //tot->start();
    }
}

void MainWindow::pushButton_clicked(Client &client)
{
    FVNPclass F;

    fvnp_num++;

    //
    int gm;
    do
    {
    cout << "Generate data, or get from Mqtt     1/2 = G/M" << endl;
    cin >> gm;
    switch(gm)
    {
    case '2' :
    {
        string mqtttopic;
        cout << "enter mqtt topic" << endl;
        cin >> mqtttopic;
        system(("python3 initialize_DB_Tables.py " + F.too_string(F.fvnp_num) + mqtttopic).c_str());
        break;
    }

    case '1' :
    {


        // Initialize client connection.
        //cout << "start connecting" << endl;
        //Client client(ClientOptions().SetHost("localhost").SetPassword("12345678"));
        //cout << "success" << endl;

        F.create_new_table_with_params(fvnp_num, client);
    }

    default :
    {
        cout << "You have a mistake, should be 'G' or 'M', try again" << endl;
    }
    }
    }while (gm!=1 || gm!=2);//do
    //

    //F.create_new_table_with_params(fvnp_num, client);
}

void MainWindow::on_pushButton_2_clicked()
{
    int tab_num;
    cout << "enter num of table" << endl;
    cin >> tab_num;

    int deep;
    cout << "enter deep" << endl;
    cin >> deep;


    FVNPclass F;
    //table observing
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    //db.setDatabaseName("mysql_db");
    db.setUserName("");
    db.setPassword("12345678");
    bool connected = db.open();

    if(!connected){
        cout << "connect fail" << endl;
        //return 1;
    }

    QSqlQueryModel model;

    string str = "select * from num_" + F.too_string(tab_num);
    const QString Q = QString::fromStdString(str);
    model.setQuery(Q);

    vector<int>p;
    vector<int>t;

    for (int i = 0; i < model.rowCount(); ++i){
        QSqlRecord record = model.record(i);

        p.push_back(record.value("param").toInt());
        t.push_back(record.value("ptime").toFloat());
    }

    if(model.rowCount()-deep >= 0){
        int total_time = t[model.rowCount()] - t[deep];
        cout << "total time = " << total_time << endl;
        cout << "total params: ";

        for(int i = deep; i < model.rowCount(); i++){
            cout << p[i] << "; ";
        }
        cout << endl;
    }
    else{
        cout << "entered deep > than deep of table" << endl;
        int total_time = t[model.rowCount()] - t[0];
        cout << "total time = " << total_time << endl;
        cout << "total params: ";

        for(int i = 0; i < model.rowCount(); i++){
            cout << p[i] << "; ";
        }
        cout << endl;
    }

}
