#include "include/prime_filter.h"

using namespace std;
using namespace std::chrono;

#include <typeinfo> //remove it 

PrimeFilter::PrimeFilter(Redis* new_redis_ptr){
    this->redis_ptr = new_redis_ptr;
}

PrimeFilter::~PrimeFilter(){
}

thread* PrimeFilter::start(){ 
    cout << "enter PrimeFilter::start()" << endl;
    
    // thread filter_thread(&PrimeFilter::filter_loop, *this);
    static thread filter_thread(&PrimeFilter::filter_loop, *this);

    cout << "exit PrimeFilter::start()" << endl;

    return &filter_thread;
}

void PrimeFilter::filter_loop(){
    cout << "enter PrimeFilter::filter_loop()" << endl;
    while(true){
        // usleep(250000); 
        // auto current_value = this->redis_ptr->brpop(NUMBER_LIST_KEY, 1);
        auto current_value = this->redis_ptr->rpop(NUMBER_LIST_KEY); //USE IT since brpop block the connection! 

        if(current_value){
            try{
                    // int number_value = stoi(current_value->second);
                    int number_value = stoi(*current_value);
                    if (is_prime(number_value)){
                        cout << "PrimeFilter::filter_loop() prime:" << number_value << endl;
                        // this->redis_ptr->sadd(PRIME_SET_KEY, current_value->second);
                        this->redis_ptr->sadd(PRIME_SET_KEY, *current_value);
                    }
                    // cout << "PrimeFilter::filter_loop() " << *current_value << " " << endl;
            }
            catch(...){
                // cout << "PrimeFilter::filter_loop() error covertation" << endl; 
            }
        }else{
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
