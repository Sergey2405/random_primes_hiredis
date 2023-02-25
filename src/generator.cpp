#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "include/generator.h"
#include <chrono>

using namespace sw::redis;
using namespace std;
using namespace std::chrono;

Generator::Generator(){
    // Generator("tcp://127.0.0.1:6379/0");
}

// Generator::Generator(const char* url){
//     auto redis = Redis(url);
//     Generator(&redis);
// }

Generator::Generator(Redis* newredis_ptr){
    redis_ptr = newredis_ptr;
}

// Generator::Generator(Redis &newredis){
//     redis_ptr = &newredis;
// }

Generator::~Generator(){
}

void Generator::start_generator_loop(int sleeptime){
    // std:thread th1(&Generator::generator_loop, this, sleeptime);
    // std:thread th1(generator_loop, sleeptime);
}

void Generator::generator_loop(int sleeptime){
// void generator_loop(int sleeptime){
    cout << "loop <1>" << endl;
    while(true){
        usleep(sleeptime*1000);
        cout << "while loop" << (system_clock::now().time_since_epoch()).count()  << endl;
    }
}

void Generator::cout_llen(){
    // auto myredis = Redis("tcp://127.0.0.1:6379/0");
    cout << "redis.llen(\"number_list:2\")=" << redis_ptr->llen("number_list:2") << endl;
    cout << typeid(*redis_ptr).name() << endl;
}
