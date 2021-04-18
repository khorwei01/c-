#include "Random1.h"
#include <cstdlib>
#include <cmath>
#include <stdint.h>

#if !defined(_MSC_VER)
using namespace std;
#endif

double GetOneGaussianBySummation()
{
    double result=0;
    for (unsigned long j=0; j < 12; j++)
        result += rand()/static_cast<double>(RAND_MAX);
        result -= 6.0;
    return result;
};

double GetOneGaussianByBoxMuller()
{
    double result;
    double x;
    double y;
    double sizeSquared;
    do
    {
        x = 2.0*rand()/static_cast<double>(RAND_MAX)-1;
        y = 2.0*rand()/static_cast<double>(RAND_MAX)-1;
        sizeSquared = x*x + y*y;
    }
    while( sizeSquared >= 1.0 || sizeSquared ==0);
    
    result = x*sqrt(-2*log(sizeSquared)/sizeSquared);

    return result;
};

/*uint64_t rol64(uint64_t x, int k)
{
    return (x << k) | (x >> (64 - k));
};

struct xoshiro256ss_state {
    uint64_t s[4] = {5,5,2,1};
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


double GetXorshiro256start(struct xoshiro256ss_state state1, struct xoshiro256ss_state state2)
{
    double rand_max = pow(2,64);
    double result;
    double x;
    double y;
    double sizeSquared;
    do
    {
        x = 2.0 * xoshiro256ss(&state1) / rand_max  -1;
        y = 2.0 *  xoshiro256ss(&state2) / rand_max -1;
        sizeSquared = x*x + y*y;
    }
    while( sizeSquared >= 1.0 || sizeSquared ==0);
    
    result = x*sqrt(-2*log(sizeSquared)/sizeSquared);

    return result;
};
*/
