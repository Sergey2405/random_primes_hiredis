#include "include/parse_config.h"

using namespace std;


ParseConfig::ParseConfig(){
    prime_range = PRIME_RANGE;
    rate_per_second = RATE_PER_SECOND;

    hiredis_host = HIREDIS_HOST;
    hiredis_port = HIREDIS_PORT;
    number_list_key = NUMBER_LIST_KEY;
    prime_set_key = PRIME_SET_KEY;
}

ParseConfig::ParseConfig(int arg_count, char * args[]){
    if(arg_count >= 6){
        try{
            prime_range = stoi((const char*)args[1]);
            cout << "ParseConfig::ParseConfig prime_range=" << prime_range << endl;
            rate_per_second = stoi((const char*)args[2]);
            cout << "ParseConfig::ParseConfig rate_per_second=" << rate_per_second << endl;

            hiredis_host = (const char*)args[3];
            cout << "ParseConfig::ParseConfig = hiredis_host" << hiredis_host << endl;
            hiredis_port = stoi((const char*)args[4]);
            cout << "ParseConfig::ParseConfig = hiredis_port" << hiredis_port << endl;
            number_list_key = (const char*)args[5];
            cout << "ParseConfig::ParseConfig = number_list_key" << number_list_key << endl;

            //enables fetch numbers
            if(arg_count >= 7) prime_set_key = (const char*)args[6];
            else prime_set_key = "";
            cout << "ParseConfig::ParseConfig prime_set_key=" << prime_set_key << endl;
        }
        catch(...){
            cout << "ParseConfig::ParseConfig error configuration" << endl;
            ParseConfig();
        }
    }else{
        cout << "ParseConfig::ParseConfig default conversation" << endl;
        ParseConfig();
    }
}

ParseConfig::~ParseConfig(){
}
