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
public:
    PrimeFilter(Redis*);
    ~PrimeFilter();

    thread* start();
    void filter_loop();
    bool is_prime(int);
};
