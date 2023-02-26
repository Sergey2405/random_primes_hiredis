#include <iostream>
#include "include/generator.h"
#include <thread>

using namespace std;

int main(int arg_count, char * args[]){
    auto mainredis = Redis(string("tcp://") + HIREDIS_HOST + ":" + to_string(HIREDIS_PORT) + "/0");
    Generator mygenerator(&mainredis, PRIME_RANGE, RATE_PER_SECOND, NUMBER_LIST_KEY);
    mygenerator.cout_llen();
    mygenerator.start_generator_loop();//ms

    return 0;
}
