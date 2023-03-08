#include "include/generator.h"

using namespace std;
using namespace std::chrono;

Generator::Generator(){
}

Generator::Generator(Redis* new_redis_ptr, int new_range, int new_rate_per_second, const char* new_number_list_key){
    this->redis_ptr = new_redis_ptr;
    this->rate_per_second = new_rate_per_second;
    this->range = new_range;
    this->number_list_key = new_number_list_key;

    this->rate_history = new long long unsigned int [this->rate_per_second]; //auto type 
    this->history_int_ptr = 0;
 
    // needs to init properly 
    long long unsigned int current_ts = (system_clock::now().time_since_epoch()).count();//auto type 
    for(int i=0; i < this->rate_per_second; i++){
        this->rate_history[i] = current_ts;
    }
}

Generator::~Generator(){
}

std::thread* Generator::start(){
    int sleeptime = 1000000 / rate_per_second; //us
    static thread generator_thread(&Generator::generator_loop, *this, sleeptime);

    return &generator_thread;
}

void Generator::generator_loop(int sleeptime){
    default_random_engine generator;
    uniform_int_distribution<int> distribution(2,this->range);
    int random_number =  distribution(generator);// the first generation is idle

    while(true){
        auto current_ts = (system_clock::now().time_since_epoch()).count();
        auto old_previoius_ts = rate_history[history_int_ptr];
        history_int_ptr = (history_int_ptr + 1) % rate_per_second;
        rate_history[history_int_ptr] = current_ts;
        if(current_ts - old_previoius_ts < 1000000000)
            usleep(sleeptime);//us
        else if(rate_per_second < 1000)         // 1 ms sleep inteval criteria
            usleep(sleeptime - sleeptime / 10); //90% sleep interval
        
        random_number =  distribution(generator);

        this->redis_ptr->lpush(this->number_list_key, to_string(random_number));
    }
}
