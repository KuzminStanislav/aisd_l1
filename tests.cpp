#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "tree.cpp"

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x * 24631) % 116640;
    return x;
}

template<typename Func>
double MeasureTime(Func&& func) {
    typedef std::chrono::steady_clock clock;
    typedef std::chrono::duration<double, std::milli> duration;

    clock::time_point start = clock::now();
    func();
    clock::time_point end = clock::now();
    return std::chronoduration_cast<duration>(end - start).count();
}

