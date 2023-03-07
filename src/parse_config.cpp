#include "include/parse_config.h"

using namespace std;
// using namespace spdlog; 

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
            // cout << "ParseConfig::ParseConfig prime_range=" << prime_range << endl; 
            // info("ParseConfig::ParseConfig prime_range={}", prime_range);
            rate_per_second = stoi((const char*)args[2]);
            // cout << "ParseConfig::ParseConfig rate_per_second=" << rate_per_second << endl; 
            // info("ParseConfig::ParseConfig rate_per_second={}", rate_per_second);

            hiredis_host = (const char*)args[3];
            // cout << "ParseConfig::ParseConfig = hiredis_host" << hiredis_host << endl; 
            // info("ParseConfig::ParseConfig hiredis_host={}", hiredis_host);
            hiredis_port = stoi((const char*)args[4]);
            // cout << "ParseConfig::ParseConfig = hiredis_port" << hiredis_port << endl; 
            // info("ParseConfig::ParseConfig hiredis_port={}", hiredis_port);
            number_list_key = (const char*)args[5];
            // cout << "ParseConfig::ParseConfig = number_list_key" << number_list_key << endl; 
            // info("ParseConfig::ParseConfig = number_list_key={}", number_list_key);

            //enables fetch numbers
            if(arg_count >= 7) prime_set_key = (const char*)args[6];
            else prime_set_key = "";
            // cout << "ParseConfig::ParseConfig prime_set_key=" << prime_set_key << endl; 
            // info("ParseConfig::ParseConfig prime_set_key=", prime_set_key);
        }
        catch(...){
            // cout << "ParseConfig::ParseConfig error configuration" << endl; 
            // error("ParseConfig::ParseConfig error configuration");
            ParseConfig();
        }
    }else{
        // cout << "ParseConfig::ParseConfig default conversation" << endl; 
        // info("ParseConfig::ParseConfig default conversation");
        ParseConfig();
    }
}

ParseConfig::~ParseConfig(){
}
