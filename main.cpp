#include "mainwindow.h"
#include <QApplication>

using namespace clickhouse;
using namespace std;

int intrand(int min, int max){
    static const double fraction = 1.0/(static_cast<double>(RAND_MAX)+1.0);

    return static_cast<int>(rand()*fraction*(max-min+1)*min);
}

string too_string(int n)
{
    char buf[40];
    sprintf(buf,"%d",n);
    return buf;
}

int tableobserver()
{
    MainWindow W;
    std::vector<int>TOid;
    std::vector<float>TOname;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    db.setDatabaseName("mysql_db");
    db.setUserName("");
    db.setPassword("");
    bool connected = db.open();

    if(!connected){
        cout << "connect fail" << endl;
        return 1;
    }

    QSqlQueryModel model;
    model.setQuery("select * from test.numbers");

    for (int i = 0; i < model.rowCount(); ++i){
        QSqlRecord record = model.record(i);

        TOid.push_back(record.value("id").toInt());
        TOname.push_back(record.value("name").toFloat());
        //Тут должен вызываться отрисовщик графика раз в 0.25 сек
        W.drawgraph(TOid, TOname);
        TOid.clear();
        TOname.clear();
    }
    return 0;
}

void clientfunc(Client& client)
{
    Block block;

    // Create a table.
    client.Execute("CREATE TABLE IF NOT EXISTS test.numbers (id UInt64, name Float64) ENGINE = Memory");

    // Insert some values
    int time = 0;
    //Let the data from the sensor be read continuously 1 time per second for 60 seconds
    //Values ​​from the sensor are in the range from 1 to 10

    //Here, a single parameter change is simulated, however, the number of parameters may be greater
    while (time<60){
        int mean = intrand(1, 10);

        auto id = std::make_shared<ColumnUInt64>();//parameter
        id->Append(mean);

        auto name = std::make_shared<ColumnFloat64>();//time
        float ftime = time;
        name->Append(ftime);

        block.AppendColumn("id"  , id);
        block.AppendColumn("name", name);

        client.Insert("test.numbers", block);

        time++;

        tableobserver();

        sleep(1);
    }

    // Select values inserted in the previous step.
    client.Select("SELECT id, name FROM test.numbers", [] (const Block& block)
    {
        {
           for (size_t i = 0; i < block.GetRowCount(); ++i) {
                std::cout << block[0]->As<ColumnUInt64>()->At(i) << " " << block[1]->As<ColumnString>()->At(i) << "\n";
            }
        }
    }
    );
    // Delete table.
    client.Execute("DROP TABLE test.numbers");
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    // Initialize client connection.
    Client client(ClientOptions().SetHost("localhost"));
    cout << "success" << endl;

    //std::thread first(clientfunc, client);
    //std::thread second(tableobserver);

    // synchronize threads:
    //first.join();                // pauses until first finishes
    //second.join();               // pauses until second finishes

    //std::cout << "foo and bar completed.\n";

    //return 0;

    clientfunc(client);

    return 0;

    return a.exec();
}
