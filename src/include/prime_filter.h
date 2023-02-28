#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif //? 

#include <sw/redis++/redis++.h>
#include <thread>
#include <iostream>
#include <math.h>

#include "config.h" 

using namespace sw::redis;
using namespace std;

class PrimeFilter{
private:
    Redis* redis_ptr = nullptr;
    int rate_per_second;
    const char* number_list_key;
    const char* prime_set_key;
public:
    PrimeFilter(Redis*, const char*, const char*);
    ~PrimeFilter();

    thread* start();
    void filter_loop();
    bool is_prime(int);
};
