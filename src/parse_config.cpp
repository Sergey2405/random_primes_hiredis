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
            rate_per_second = stoi((const char*)args[2]);

            hiredis_host = (const char*)args[3];
            hiredis_port = stoi((const char*)args[4]);
            number_list_key = (const char*)args[5];

            //enables fetch numbers
            if(arg_count >= 7) prime_set_key = (const char*)args[6];
            else prime_set_key = "";
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
