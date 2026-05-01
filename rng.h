#pragma once

#include <cstdint>

class RNG {
public:
    RNG();
    double Next();
private:
    int s1, s2, s3;
    uint64_t n;
};