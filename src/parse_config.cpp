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
    try{
        // prime_range = stoi(args[0]);
        prime_range = stoi((const char*)args[1]);
        // rate_per_second #include <string>= stoi(args[1]);
        rate_per_second = stoi((const char*)args[2]);

        // cout << (const char*)args[3] << endl
        cout << (const char*)args[1] << endl
             << (const char*)args[2] << endl
             << (const char*)args[3] << endl
             << (const char*)args[4] << endl
             << (const char*)args[5] << endl
             << (const char*)args[6] << endl;
        hiredis_host = (const char*)args[3];
        hiredis_port = stoi((const char*)args[4]);
        number_list_key = (const char*)args[5];
        prime_set_key = (const char*)args[6];
    }
    catch(...){
        cout << "ParseConfig::ParseConfig error conversation" << endl;
        ParseConfig();
        // prime_range = PRIME_RANGE;
        // rate_per_second = RATE_PER_SECOND;

        // hiredis_host = HIREDIS_HOST;
        // hiredis_port = HIREDIS_PORT;
        // number_list_key = NUMBER_LIST_KEY;
        // prime_set_key = PRIME_SET_KEY;
    }
}

ParseConfig::~ParseConfig(){
}

