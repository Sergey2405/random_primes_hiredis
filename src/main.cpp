#include <iostream>
#include "include/generator.h"
#include <thread>

using namespace std;

int main(int arg_count, char * args[]){
    auto mainredis = Redis("tcp://127.0.0.1:6379/0");
    Generator mygenerator(&mainredis, 2000);
    mygenerator.cout_llen();
    // cout << "before thread" << endl;
    mygenerator.start_generator_loop();//ms
    // cout << "after thread" << endl;

    std::cout << "popka" << endl;
    return 0;
}
