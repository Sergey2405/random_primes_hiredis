// #include <iostream> 
#include <spdlog/spdlog.h>
#include "include/parse_config.h"
#include "include/generator.h"
#include "include/prime_filter.h"

using namespace std;
// using namespace spdlog; 

// ./random_primes_hiredis 1000000 1 "127.0.0.1" 6379 "number_list:2" "prime_set:2"
int main(int arg_count, char * args[]){
    // set_level(spdlog::level::info);

    ParseConfig parsed_config(arg_count, args);

    auto main_redis = Redis(string("tcp://") + parsed_config.get_redis_host() + ":" +
                            to_string(parsed_config.get_redis_port()) + "/0");
    
    Generator main_generator(&main_redis, parsed_config.get_prime_range(),
                             parsed_config.get_rate_per_second(), parsed_config.get_number_list_key());
    thread* main_generator_thread_ptr;
    if(parsed_config.get_prime_range() > 2 && parsed_config.get_rate_per_second() > 0)
        main_generator_thread_ptr = main_generator.start();

    PrimeFilter main_prime_filter(&main_redis,
                                  parsed_config.get_number_list_key(), parsed_config.get_prime_set_key());
    thread* main_prime_filter_thread_ptr;
    if(strcmp(parsed_config.get_prime_set_key(), ""))
        main_prime_filter_thread_ptr = main_prime_filter.start();

    if(parsed_config.get_prime_range() > 2 && parsed_config.get_rate_per_second() > 0)
        main_generator_thread_ptr->join();
    if((parsed_config.get_prime_set_key() != ""))
        main_prime_filter_thread_ptr->join();

    return 0;
}
