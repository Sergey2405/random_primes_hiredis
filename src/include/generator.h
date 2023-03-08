#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <sw/redis++/redis++.h>
#include <thread>
#include <chrono>
#include <random>
#include <string>

#include "config.h"

using namespace sw::redis;

class Generator{
private:
    Redis* redis_ptr = nullptr;
    signed int rate_per_second;
    signed int range;
    const char* number_list_key;

    long long unsigned int* rate_history;
    unsigned int history_int_ptr = 0;

public:
    Generator();
    Generator(Redis*, int, int, const char*);
    ~Generator();

    std::thread* start();
    void generator_loop(int);
};