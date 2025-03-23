#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "tree.cpp"
#include "tests.cpp"

int main() {
    //time tests

    const size_t sizes[] = {1000, 10000, 100000};
    const size_t attemps = 100;

    for (size_t size : sizes) {
        std::cout << "Size: " << size << std::endl;

        size_t fill_time = TestFillTime(size, attemps);
        std::cout << "Average tree filling time: " << fill_time << "ns" << std::endl;

        size_t search_time = TestSearchTime(size, attemps);
        std::cout << "Average tree searching time: " << search_time << "ns" << std::endl;

        size_t add_time = TestAddTime(size, attemps);
        std::cout << "Average tree adding time: " << add_time << "ns" << std::endl;

        size_t erase_time = TestEraseTime(size, attemps);
        std::cout << "Average tree erasing time: " << erase_time << "ns" << std::endl;

        size_t vec_fill_time = TestVecFillTime(size, attemps);
        std::cout << "Average vector filling time: " << vec_fill_time << "ns" << std::endl;

        size_t vec_search_time = TestVecSearchTime(size, attemps);
        std::cout << "Average vector searching time: " << vec_search_time << "ns" << std::endl;

        size_t vec_add_time = TestVecAddTime(size, attemps);
        std::cout << "Average vector adding time: " << vec_add_time << "ns" << std::endl;

        size_t vec_erase_time = TestVecEraseTime(size, attemps);
        std::cout << "Average vector erasing time: " << vec_erase_time << "ns" << std::endl;

        std::cout << "--------------------" << std::endl << std::endl;
    }
    return 0;
}
