#include <spdlog/spdlog.h>
#include "include/parse_config.h"
#include "include/generator.h"
#include "include/prime_filter.h"

const char* global_log_level;

void set_global_log_level(){
    if     (!strcmp(global_log_level, "trace"   )) spdlog::set_level(spdlog::level::trace   );
    else if(!strcmp(global_log_level, "trace"   )) spdlog::set_level(spdlog::level::trace   );
    else if(!strcmp(global_log_level, "debug"   )) spdlog::set_level(spdlog::level::debug   );
    else if(!strcmp(global_log_level, "info"    )) spdlog::set_level(spdlog::level::info    );
    else if(!strcmp(global_log_level, "warn"    )) spdlog::set_level(spdlog::level::warn    );
    else if(!strcmp(global_log_level, "err"     )) spdlog::set_level(spdlog::level::err     );
    else if(!strcmp(global_log_level, "critical")) spdlog::set_level(spdlog::level::critical);
    else                                     spdlog::set_level(spdlog::level::off);
}

// ./random_primes_hiredis 100000000 20 192.168.0.14 6379 number_list:2 prime_set:2 debug
int main(int arg_count, char * args[]){

    // set info at first before parsing config
    spdlog::set_level(spdlog::level::info);

    ParseConfig parsed_config(arg_count, args);
    global_log_level = parsed_config.get_log_level();
    set_global_log_level();

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
