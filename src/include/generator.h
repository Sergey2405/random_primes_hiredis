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
    Redis* redis_ptr = nullptr;
    int rate_per_second;
    long long int* rate_history;
    int history_int_ptr = 0;
public:
    Generator();
    // Generator(const char*);
    // Generator(Redis*);
    Generator(Redis*, int);
    ~Generator();

    void start_generator_loop();
    void generator_loop(int);
    void cout_llen();
};