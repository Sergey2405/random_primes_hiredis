#include "include/generator.h"

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

Generator::Generator(Redis* newredis_ptr, int rate_per_second){
    redis_ptr = newredis_ptr;
    this->rate_per_second = rate_per_second;
    this->rate_history = new long int[this->rate_per_second];
    // memset(this->rate_history, 777, rate_per_second * sizeof(int));
    // this->rate_history = new int[this->rate_per_second](999);
    this->history_int_ptr = 0;


    // int current_ts = (system_clock::now().time_since_epoch()).count();
    for(int i=0; i < this->rate_per_second; i++){ 
        static int current_ts = (system_clock::now().time_since_epoch()).count();
        this->rate_history[i] = current_ts; 
    }

    for(int i=0; i < this->rate_per_second; i++){ 
        cout << this->rate_history[i] << endl; 
    } 
}

// Generator::Generator(Redis &newredis){
//     redis_ptr = &newredis;
// }

Generator::~Generator(){
}

void Generator::start_generator_loop(int sleeptime){
    thread th1(&Generator::generator_loop, *this, sleeptime);
    th1.join();
}

void Generator::generator_loop(int sleeptime){
// void generator_loop(int sleeptime){
    cout << "loop <1>" << endl;
    while(true){
        usleep(sleeptime*1000);
        cout << "while loop " << (system_clock::now().time_since_epoch()).count()  << endl;
    }
}

void Generator::cout_llen(){
    // auto myredis = Redis("tcp://127.0.0.1:6379/0");
    cout << "redis.llen(\"number_list:2\")=" << redis_ptr->llen("number_list:2") << endl;
    cout << typeid(*redis_ptr).name() << endl;
}
