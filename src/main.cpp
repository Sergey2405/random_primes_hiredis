#include <iostream>
#include "include/generator.h"
#include <thread>

using namespace std;

int main(int arg_count, char * args[]){
    auto mainredis = Redis("tcp://127.0.0.1:6379/0");
    Generator mygenerator(&mainredis, 500);
    mygenerator.cout_llen();
    // cout << "before thread" << endl;
    // thread th1(&Generator::generator_loop, mygenerator, 1000);//ms
    // mygenerator.start_generator_loop(500);//ms
    // th1.join();
    // cout << "after thread" << endl;

    std::cout << "popka" << endl;
    return 0;
}
