#include "include/generator.h"

using namespace sw::redis;
using namespace std;

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

void Generator::cout_llen(){
    // auto myredis = Redis("tcp://127.0.0.1:6379/0");
    cout << "redis.llen(\"number_list:2\")=" << redis_ptr->llen("number_list:2") << endl;
    cout << typeid(*redis_ptr).name() << endl;
}
