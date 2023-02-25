#include <sw/redis++/redis++.h>
#include <iostream>

using namespace sw::redis;

// class Generator : public Redis{
class Generator{
private:
    // sw::redis::Redis myredis;
    // Redis::Redis myredis;
    Redis* redis_ptr = nullptr;//works
    // sw::redis::Redis myredis = Redis("tcp://127.0.0.1:6379/0");// works
    // Redis genredis = Redis("tcp://127.0.0.1:6379/0");// works
public:
    Generator();
    // Generator(const char*);
    Generator(Redis*);
    // Generator(Redis);
    
    ~Generator();

    void cout_llen();
};