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
        // auto current_value = this->redis_ptr->brpop(NUMBER_LIST_KEY, 5);
        auto current_value = this->redis_ptr->rpop(NUMBER_LIST_KEY);

        if(current_value){
            try{
                    // cout
                    cout << "PrimeFilter::filter_loop() " << *current_value << " "
                    // << stoi(*current_value)+1
                         <<" type: " << typeid(current_value).name() << endl;
            }
            catch(...){
                cout << "PrimeFilter::filter_loop() error covertation" << endl; 
            }
        }else{
            cout << "PrimeFilter::filter_loop() nullptr" << endl;
        }
    }
}

