#include <iostream> //for debug 
#include <string> //?
#include "config.h"

class ParseConfig{
private:
    int prime_range = PRIME_RANGE;
    int rate_per_second = RATE_PER_SECOND;

    const char* hiredis_host = HIREDIS_HOST;
    int hiredis_port = HIREDIS_PORT;
    const char* number_list_key = NUMBER_LIST_KEY;
    const char* prime_set_key = PRIME_SET_KEY;

public:
    ParseConfig();
    // ParseConfig(int, char*);
    ParseConfig(int arg_count, char * args[]);
    ~ParseConfig();

    int get_prime_range(){return prime_range;};
    int get_rate_per_second(){return rate_per_second;};

    const char* get_redis_host(){return hiredis_host;};
    int get_redis_port(){return hiredis_port;};
    const char* get_number_list_key(){return number_list_key;};
    const char* get_prime_set_key(){return prime_set_key;};
};