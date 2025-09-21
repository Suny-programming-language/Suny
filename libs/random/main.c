#include "C:/Suny/src/Suny.h"
#include <stdint.h>
#include <time.h>
#include <windows.h>

static uint64_t s[2];
static int seeded = 0;

uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

void seed_xoshiro_runtime() {
    uint64_t t = (uint64_t)time(NULL);
    uint64_t c = (uint64_t)clock();
    uint64_t pid = (uint64_t)GetCurrentProcessId();

    s[0] = t ^ 0xdeadbeef12345678ULL ^ c ^ pid;
    s[1] = (t << 32) | (t >> 32) ^ (c << 16) ^ pid;

    seeded = 1;
}

float random_xoshiro() {
    if (!seeded) seed_xoshiro_runtime();

    uint64_t s0 = s[0];
    uint64_t s1 = s[1];
    uint64_t result = s0 + s1;

    s1 ^= s0;
    s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14);
    s[1] = rotl(s1, 36);

    return (float)((result >> 11) * (1.0 / 9007199254740992.0));
}

SUNY_API struct Sobj* Srandom(struct Sframe* frame) {
    float result = random_xoshiro();
    return Sobj_set_int(result);
}