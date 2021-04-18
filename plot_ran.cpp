#define _USE_MATH_DEFINES 

#include <iostream>
#include <stdint.h>
#include <cmath>
#include <chrono>
#include "Random1.h"


uint64_t rol64(uint64_t x, int k)
{
    return (x << k) | (x >> (64 - k));
};

struct xoshiro256ss_state {
    uint64_t s[4] = {};
};

uint64_t xoshiro256ss(struct xoshiro256ss_state *state)
{
    uint64_t *s = state->s;
    uint64_t const result = rol64(s[1] * 5, 7) * 9;
    uint64_t const t = s[1] << 17;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= t;
    s[3] = rol64(s[3], 45);

    return result;
};

uint64_t * seed_gen(uint64_t number){
    uint64_t four_d_seed = number%10000;
    static uint64_t sample_array[4] = {2, 3, 6, 1};
    if (four_d_seed !=0){
        for (int i = 3; i > -1 ; i--){
            sample_array[i] = four_d_seed % 10;
            four_d_seed = four_d_seed / 10;
        }
    }else{}
    return sample_array;
};

double GetXorshiro256start()
{
    double rand_max = pow(2,64);
    double result;
    double x;
    double y;
    double sizeSquared;
    std::chrono::system_clock::time_point ts = std::chrono::system_clock::now();
    int dtn = std::chrono::duration_cast<std::chrono::nanoseconds>(ts.time_since_epoch()).count();
    xoshiro256ss_state seed;
    int number = dtn % 10000;
    if (number != 0){
        for (int i=3; i>-1; i--){
            seed.s[i] = number % 10;
            number  = number / 10;
        }
    }
    else {}
    //struct xoshiro256ss_state seed2;
    do
    {
        x = 2.0* xoshiro256ss(&seed) / rand_max-1;
        y = 2.0* xoshiro256ss(&seed) / rand_max-1;
        sizeSquared = x*x + y*y;
        std::cout<< x <<std::endl;
        std::cout<< y <<std::endl;
    }
    while( sizeSquared >= 1.0 || sizeSquared ==0);
    
    result = x*sqrt(-2*log(sizeSquared)/sizeSquared);

    return result;
};


int main(){
    const int m = 20000;
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < m ; i++){
        std::cout<< GetXorshiro256start() <<std::endl;
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    auto t3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < m ; i++){
        std::cout<< GetOneGaussianByBoxMuller() <<std::endl;
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::chrono::duration<double, std::milli> ms_double1 = t4 - t3;
    std::cout << ms_double.count() << "ms";
    std::cout << ms_double1.count() << "ms";
    //if (result >1 || result <0){
    //    printf("error");
    //    break;
    //}
    //printf("%f",result);
    
}