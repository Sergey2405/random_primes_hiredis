#include <iostream>
#include "include/parse_config.h"
#include "include/generator.h"
#include "include/prime_filter.h"

using namespace std;

        // prime_range = stoi(args[0]);
        // rate_per_second = stoi(args[1]);

        // hiredis_host = args[2];
        // hiredis_port = stoi(args[3]);
        // number_list_key = args[4];
        // prime_set_key = args[5];

// #define NUMBER_LIST_KEY "number_list:2"
// #define PRIME_SET_KEY "prime_set:2"

// ./random_primes_hiredis 1000000 1 "127.0.0.1" 6379 "number_list:2" "prime_set:2"
int main(int arg_count, char * args[]){

    // ParseConfig parsed_config;
    ParseConfig parsed_config(arg_count, args);

    // auto main_redis = Redis(string("tcp://") + HIREDIS_HOST + ":" + to_string(HIREDIS_PORT) + "/0");
    auto main_redis = Redis(string("tcp://") + parsed_config.get_redis_host() + ":" +
                            to_string(parsed_config.get_redis_port()) + "/0");
    
    // Generator main_generator(&main_redis, PRIME_RANGE, RATE_PER_SECOND, NUMBER_LIST_KEY);
    Generator main_generator(&main_redis, parsed_config.get_prime_range(),
                             parsed_config.get_rate_per_second(), parsed_config.get_number_list_key());
    thread* main_generator_thread_ptr = main_generator.start();
    cout << "main main_generator.start() ed" << endl;

    PrimeFilter main_prime_filter(&main_redis);
    thread* main_prime_filter_thread_ptr = main_prime_filter.start();

    main_generator_thread_ptr->join();
    main_prime_filter_thread_ptr->join();

    return 0;
}
