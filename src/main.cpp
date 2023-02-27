#include <iostream>
#include "include/generator.h"
#include "include/prime_filter.h"
// #include <thread>

using namespace std;

int main(int arg_count, char * args[]){
    auto main_redis = Redis(string("tcp://") + HIREDIS_HOST + ":" + to_string(HIREDIS_PORT) + "/0");
    
    Generator main_generator(&main_redis, PRIME_RANGE, RATE_PER_SECOND, NUMBER_LIST_KEY);
    auto main_generator_thread = main_generator.start();
    thread* main_generator_thread_ptr = main_generator.start();
    cout << "main main_generator.start() ed" << endl;
    // main_generator.cout_llen(); // remove it 

    PrimeFilter main_prime_filter(&main_redis);
    thread* main_prime_filter_thread_ptr = main_prime_filter.start();

    main_generator_thread_ptr->join();
    main_prime_filter_thread_ptr->join();

    return 0;
}
