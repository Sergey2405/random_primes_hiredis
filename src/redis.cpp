#include "include/redis.h"

using namespace sw::redis;

int main(void) {
    auto redis = Redis("tcp://127.0.0.1:6379/0");
    std::cout << redis.ping() << std::endl;
    std::cout << "redis.llen(\"number_list:2\")=" << redis.llen("number_list:2") << std::endl;
    std::cout << "redis.scard(\"prime_set:2\")=" << redis.scard("prime_set:2") << std::endl;
}

