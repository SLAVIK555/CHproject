#ifndef FVNPCLASS_H
#define FVNPCLASS_H

#include <iostream>
#include <string>

#include <unistd.h>

#include "clickhouse/client.h"

using namespace std;
using namespace clickhouse;

class FVNPclass
{
public:
    FVNPclass();
    int fvnp_num = 0;
    std::string paramname;

    int classintrand(int min, int max);

    string too_const_string(string str, int n);
    string too_string(int n);
    string ftoo_string(float n);

    void create_new_table_with_params(int fvnp_num, Client& client);
    void insert_new_params(int fvnp_num, int param, float ptime, Client& client);

    virtual void clientfunc(Client& client);


    //const auto param = std::make_shared<ColumnUInt64>();//parameter;
    //auto ptime = std::make_shared<ColumnFloat64>();//time;



};

#endif // FVNPCLASS_H
