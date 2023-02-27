#include "include/generator.h"

// using namespace sw::redis; 
using namespace std;
using namespace std::chrono;

Generator::Generator(){
}

// Generator::Generator(const char* url){
//     auto redis = Redis(url);
//     Generator(&redis);
// }

Generator::Generator(Redis* new_redis_ptr, int new_range, int new_rate_per_second, const char* new_number_list_key){
    this->redis_ptr = new_redis_ptr;
    this->rate_per_second = new_rate_per_second;
    this->range = new_range;
    this->number_list_key = new_number_list_key;

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

Generator::~Generator(){
}

std::thread* Generator::start(){
    cout << "enter Generator::start()" << endl;
    int sleeptime = 1000000 / rate_per_second; //us
    static thread generator_thread(&Generator::generator_loop, *this, sleeptime);

    cout << "join Generator::start()" << endl;
    cout << "exit Generator::start()" << endl;
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

        this->redis_ptr->lpush(NUMBER_LIST_KEY, to_string(random_number)); 

        // cout << "while loop " <<  history_int_ptr << " " << rate_history[history_int_ptr]
        //      << " " << random_number << endl;
    }
}

void Generator::cout_llen(){
    // auto myredis = Redis("tcp://127.0.0.1:6379/0");
    // cout << "redis.llen(\"number_list:2\")=" << redis_ptr->llen("number_list:2") << endl;
    cout << "redis.llen(\"number_list:2\")=" << redis_ptr->llen(NUMBER_LIST_KEY) << endl;
    cout << typeid(*redis_ptr).name() << endl;
}

