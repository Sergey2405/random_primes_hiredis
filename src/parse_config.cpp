#include "include/parse_config.h"

using namespace std;

extern const char* global_log_level;

ParseConfig::ParseConfig(){
    prime_range = PRIME_RANGE;
    rate_per_second = RATE_PER_SECOND;

    hiredis_host = HIREDIS_HOST;
    hiredis_port = HIREDIS_PORT;
    number_list_key = NUMBER_LIST_KEY;
    prime_set_key = PRIME_SET_KEY;
    log_level = GLOBAL_LOG_LEVEL;
}

ParseConfig::ParseConfig(int arg_count, char * args[]){
    if(arg_count >= 6){
        try{
            prime_range = stoi((const char*)args[1]);
            spdlog::info("ParseConfig::ParseConfig prime_range={}", prime_range);
            rate_per_second = stoi((const char*)args[2]);
            spdlog::info("ParseConfig::ParseConfig rate_per_second={}", rate_per_second);

            hiredis_host = (const char*)args[3];
            spdlog::info("ParseConfig::ParseConfig hiredis_host={}", hiredis_host);
            hiredis_port = stoi((const char*)args[4]);
            spdlog::info("ParseConfig::ParseConfig hiredis_port={}", hiredis_port);
            number_list_key = (const char*)args[5];
            spdlog::info("ParseConfig::ParseConfig number_list_key={}", number_list_key);

            //enables fetch numbers
            if((arg_count >= 7) &&
               (strcmp((const char*)args[6], "trace")) &&
               (strcmp((const char*)args[6], "debug")) &&
               (strcmp((const char*)args[6], "info" )) &&
               (strcmp((const char*)args[6], "warn" )) &&
               (strcmp((const char*)args[6], "err"  )) &&
               (strcmp((const char*)args[6], "critical" ))){
                prime_set_key = (const char*)args[6];
            }
            else{
                prime_set_key = "";
            }

            spdlog::info("ParseConfig::ParseConfig prime_set_key={}", prime_set_key);

            log_level = GLOBAL_LOG_LEVEL;
            if((!strcmp((const char*)args[arg_count - 1], "trace"   )) ||
               (!strcmp((const char*)args[arg_count - 1], "debug"   )) ||
               (!strcmp((const char*)args[arg_count - 1], "info"    )) ||
               (!strcmp((const char*)args[arg_count - 1], "warn"    )) ||
               (!strcmp((const char*)args[arg_count - 1], "err"     )) ||
               (!strcmp((const char*)args[arg_count - 1], "critical")))
            {
                log_level = (const char*)args[arg_count - 1];
            }

            spdlog::info("ParseConfig::ParseConfig log_level={}", log_level);
        }
        catch(...){
            spdlog::error("ParseConfig::ParseConfig error configuration");
            ParseConfig();
        }
    }else{
        spdlog::info("ParseConfig::ParseConfig default conversation");
        ParseConfig();
    }
}

ParseConfig::~ParseConfig(){
}
