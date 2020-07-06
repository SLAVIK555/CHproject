#include "fvnpclass.h"

FVNPclass::FVNPclass()
{

}

int FVNPclass::classintrand(int min, int max){
    static const double fraction = 1.0/(static_cast<double>(RAND_MAX)+1.0);

    return static_cast<int>(rand()*fraction*(max-min+1)*min);
}

string FVNPclass::too_const_string(string str, int n){
    char buf[250];
    sprintf(buf,"%s",str);
    sprintf(buf,"%d",n);
    return buf;
}

string FVNPclass::too_string(int n)
{
    char buf[40];
    sprintf(buf,"%d",n);
    return buf;
}

string FVNPclass::ftoo_string(float n){
    char buf[80];
    sprintf(buf,"%f",n);
    return buf;
}

void FVNPclass::create_new_table_with_params(int fvnp_num, Client &client){
    //"CREATE TABLE IF NOT EXISTS test.numbers (param UInt64, ptime Float64) ENGINE = Memory"
    string Ctable = "CREATE TABLE IF NOT EXISTS num_" + too_string(fvnp_num) + " (param UInt64, ptime Float64) ENGINE = Memory";

    client.Execute(Ctable);

    cout << "created" << Ctable << endl;
}

void FVNPclass::insert_new_params(int fvnp_num, int param, float ptime, Client &client){
    //"INSERT INTO " + too_string(fvnp_num) + "_num (param, ptime) VALUES (" + too_string(param) + ", " + too_string(ptime) + ")"
    string Iparams = "INSERT INTO num_" + too_string(fvnp_num) + " (param, ptime) VALUES (" + too_string(param) + ", " + ftoo_string(ptime) + ")";

    cout << Iparams << endl;

    client.Execute(Iparams);
}

void FVNPclass::clientfunc(Client &client){
    //Block block;

    // Create a table.
    create_new_table_with_params(fvnp_num, client);

    // Generate and insert values
    int time = 0;
    //Let the data from the sensor be read continuously 1 time per second for 60 seconds
    //Values ​​from the sensor are in the range from 1 to 10
    cout << "stear cycle" << endl;
    while (time<60){
    //cout << "in cycle" << endl;
         float classftime = time;

         for (int i=0; i<fvnp_num+1; i++){
         int classmean = classintrand(1, 10);

         insert_new_params(fvnp_num, classmean, classftime, client);
         cout << "in cycle" << endl;
         }

         time++;
         sleep(1);
     }

     // Delete table.
     client.Execute("DROP TABLE test.numbers");
}
