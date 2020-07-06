#include "mainwindow.h"
#include "fvnpclass.h"
#include <QApplication>

#include <QTimer>

int intrand(int min, int max){
    static const double fraction = 1.0/(static_cast<double>(RAND_MAX)+1.0);

    return static_cast<int>(rand()*fraction*(max-min+1)*min);
}

/*void clientfunc(Client& client)
{
    FVNPclass F;
    Block block;

    // Create a table.
    //F.create_new_table_with_params(FVNPclass::fvnp_num, client);
    //client.Execute("CREATE TABLE IF NOT EXISTS test.numbers (param UInt64, ptime Float64) ENGINE = Memory");

    // Insert some values
    int time = 0;
    //Let the data from the sensor be read continuously 1 time per second for 60 seconds
    //Values ​​from the sensor are in the range from 1 to 10

    //Here, a single parameter change is simulated, however, the number of parameters may be greater
    //vector< make_shared<clickhouse::ColumnUInt64> > parr;
    client.Execute("ALTER TABLE test.numbers ADD COLUMN s String ");
    auto param = std::make_shared<ColumnUInt64>();//parameter
    auto ptime = std::make_shared<ColumnFloat64>();//time
    auto par = param;

    while (time<60){
        int mean = intrand(1, 10);
        param->Append(mean);

        float ftime = time;
        ptime->Append(ftime);

        block.AppendColumn("param"  , param);
        block.AppendColumn("ptime", ptime);

        client.Insert("test.numbers", block);

        time++;

        //tableobserver();

        sleep(1);
    }

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
}*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    FVNPclass F;
    //F.create_new_table_with_params(0);
    //F.insert_new_params(0, 6, 7.3);

    // Initialize client connection.
    cout << "start connecting" << endl;
    Client client(ClientOptions().SetHost("localhost").SetPassword("12345678"));
    cout << "success" << endl;

    F.clientfunc(client);
    //F.insert_new_params(0, 6, 7.3);

    //clientfunc(client);

    return 0;

    //return a.exec();
}
