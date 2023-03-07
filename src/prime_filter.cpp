#include "include/prime_filter.h"

using namespace std;
using namespace std::chrono;
// using namespace spdlog; 

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
    
    static thread filter_thread(&PrimeFilter::filter_loop, *this);
    return &filter_thread;
}

void PrimeFilter::filter_loop(){
    // set_level(spdlog::level::debug); 
    while(true){
        //USE IT since brpop block the connection!
        auto current_value = this->redis_ptr->rpop(this->number_list_key);

        if(current_value){
            try{
                int number_value = stoi(*current_value);
                if (is_prime(number_value)){
                    // cout << "PrimeFilter::filter_loop() prime:" << number_value << endl;  
                    spdlog::debug("PrimeFilter::filter_loop() prime: {}", number_value);
                    this->redis_ptr->sadd(this->prime_set_key, *current_value);
                }
            }
            catch(...){
                // cout << "PrimeFilter::filter_loop() error covertation" << *current_value << endl; 
                spdlog::warn("PrimeFilter::filter_loop() error convertation {}", *current_value); 
                // spdlog::warn("PrimeFilter::filter_loop() error convertation");
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
