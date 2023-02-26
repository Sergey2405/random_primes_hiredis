#include "include/generator.h"

using namespace sw::redis;
using namespace std;
using namespace std::chrono;

Generator::Generator(){
}

// Generator::Generator(const char* url){
//     auto redis = Redis(url);
//     Generator(&redis);
// }

Generator::Generator(Redis* newredis_ptr, int rate_per_second){
    redis_ptr = newredis_ptr;
    this->rate_per_second = rate_per_second;
    this->rate_history = new long long int [this->rate_per_second]; //auto type 
    this->history_int_ptr = 0;

    // needs to init properly 
    long long int current_ts = (system_clock::now().time_since_epoch()).count();//auto type 
    for(int i=0; i < this->rate_per_second; i++){ 
        // static int current_ts = (system_clock::now().time_since_epoch()).count();
        this->rate_history[i] = current_ts; 
    }

    // for(int i=0; i < this->rate_per_second; i++){ 
    //     cout << this->rate_history[i] << endl; 
    // } 
}

// Generator::Generator(Redis &newredis){
//     redis_ptr = &newredis;
// }

Generator::~Generator(){
}

void Generator::start_generator_loop(){
    int sleeptime = 1000000 / rate_per_second; //us
    thread generator_thread(&Generator::generator_loop, *this, sleeptime);
    generator_thread.join();
}

void Generator::generator_loop(int sleeptime){
    // auto current_ts = (system_clock::now().time_since_epoch()).count();
    while(true){
        auto current_ts = (system_clock::now().time_since_epoch()).count();
        auto old_previoius_ts = rate_history[history_int_ptr];
        history_int_ptr = (history_int_ptr + 1) % rate_per_second;
        rate_history[history_int_ptr] = current_ts;
        if(current_ts - old_previoius_ts < 1000000000)
            usleep(sleeptime);//ns
        else if(rate_per_second < 1000)         // 1 ms sleep inteval criteria
            usleep(sleeptime - sleeptime / 10); //90% sleep interval
        cout << "while loop " <<  history_int_ptr << " " << rate_history[history_int_ptr] << endl;
    }
}

void Generator::cout_llen(){
    // auto myredis = Redis("tcp://127.0.0.1:6379/0");
    cout << "redis.llen(\"number_list:2\")=" << redis_ptr->llen("number_list:2") << endl;
    cout << typeid(*redis_ptr).name() << endl;
}
