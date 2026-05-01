#include <chrono>
#include <cstdint>
#include "rng.h"

using namespace std::chrono;

RNG::RNG() {
    n = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    s1 = n % 30268 + 1;
    s2 = n % 30306 + 1;
    s3 = n % 30322 + 1;
}

double RNG::Next() {
    s1 = (171 * s1) % 30269;
    s2 = (172 * s2) % 30307;
    s3 = (170 * s3) % 30323;
    return (s1/30269.0 + s2/30307.0 + s3/30323.0) - static_cast<int>(s1/30269.0 + s2/30307.0 + s3/30323.0);
}