#include "mainwindow.h"
#include <QApplication>

#include <QTimer>

int intrand(int min, int max){
    static const double fraction = 1.0/(static_cast<double>(RAND_MAX)+1.0);

    return static_cast<int>(rand()*fraction*(max-min+1)*min);
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

        //tableobserver();

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
    //Client client(ClientOptions().SetHost("localhost"));
    //cout << "success" << endl;

    //clientfunc(client);

    //return 0;

    return a.exec();
}
