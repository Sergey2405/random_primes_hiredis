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
        auto current_value = *this->redis_ptr->rpop(NUMBER_LIST_KEY);
        // string current_value = this->redis_ptr->rpop(NUMBER_LIST_KEY);
        // char* current_number = this->redis_ptr->rpop(NUMBER_LIST_KEY);
        // cout << current_number << " type: " << typeid(current_number).name() << endl;
        // string current_value_string = string(current_value);
        // cout << "PrimeFilter::filter_loop() " << string(current_value_string) << " type: " << typeid(current_value_string).name() << endl;
        // cout << "PrimeFilter::filter_loop() " << " type: " << typeid(current_value).name() << endl;
        // cout << "PrimeFilter::filter_loop() " << *(this->redis_ptr->rpop(NUMBER_LIST_KEY)) << " type: " << typeid(current_value).name() << endl;
        cout << "PrimeFilter::filter_loop() " << current_value << " type: " << typeid(current_value).name() << endl;
        usleep(1000000);

    }
}

