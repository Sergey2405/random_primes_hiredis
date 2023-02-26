#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <sw/redis++/redis++.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace sw::redis;

// class Generator : public Redis{
class Generator{
private:
    Redis* redis_ptr = nullptr;//works
    int rate_per_second;
    long int* rate_history;
    int history_int_ptr = 0;
    // sw::redis::Redis myredis = Redis("tcp://127.0.0.1:6379/0");// works
    // Redis genredis = Redis("tcp://127.0.0.1:6379/0");// works
public:
    Generator();
    // Generator(const char*);
    // Generator(Redis*);
    Generator(Redis*, int);
    ~Generator();

    void start_generator_loop(int);
    void generator_loop(int);
    void cout_llen();
};