#include "include/prime_filter.h"

using namespace std;
using namespace std::chrono;

extern void set_global_log_level();

PrimeFilter::PrimeFilter(Redis* new_redis_ptr,
                         const char* new_number_list_key,
                         const char* new_prime_set_key){
    this->redis_ptr = new_redis_ptr;
    this->number_list_key = new_number_list_key;
    this->prime_set_key = new_prime_set_key;
}

PrimeFilter::~PrimeFilter(){
}

thread* PrimeFilter::start(){ 
    //determines log level in this thread
    set_global_log_level();
    static thread filter_thread(&PrimeFilter::filter_loop, *this);
    return &filter_thread;
}

void PrimeFilter::filter_loop(){
    while(true){
        //USE IT since brpop block the connection!
        auto current_value = this->redis_ptr->rpop(this->number_list_key);

        if(current_value){
            try{
                int number_value = stoi(*current_value);
                if (is_prime(number_value)){
                    spdlog::debug("PrimeFilter::filter_loop() prime: {}", number_value);
                    this->redis_ptr->sadd(this->prime_set_key, *current_value);
                }
            }
            catch(...){
                spdlog::warn("PrimeFilter::filter_loop() error convertation {}", *current_value);
            }
        }else{
            spdlog::debug("PrimeFilter::filter_loop() sleep for one second");
            usleep(1000000);   //1 sec
        }
    }
}

bool PrimeFilter::is_prime(int number){
    bool result=true;
    if(number % 2 == 0) return false;
    int criteria = (int)sqrt(number);
    for(int i = 3;
        i < criteria;
        i += 2){
        if(number % i == 0){
            number/=i;
            criteria = (int)sqrt(number);
            result=false;
            break;
        }
    }
    return result;
}
