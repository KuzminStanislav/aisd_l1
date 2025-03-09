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

void TestFillTime(size_t size, BinaryTree<int>& tree) {
    double avg_f_time = 0;
    for (size_t i = 0; i < 100; ++i) {
        tree = BinaryTree<int>();
        avg_f_time += MeasureTime([&]() {
            for (size_t j = 0; j < size, ++j;) {
                tree.insert(lcg());
            }
            });
    }

    avg_f_time /= 100;
    std::cout << "Average filling tree time : " << avg_f_time << "mks" << std::endl;
}

void TestSearchTime(size_t size, BinaryTree<int>& tree) {
    double avg_s_time = 0;
    for (size_t i = 0; i < 1000; ++i) {
        avg_s_time += MeasureTime([&]() {
            tree.contains(lcg());
        });
    }

    avg_s_time /= 1000;
    std::cout << "Average time for searching in tree: " << avg_s_time << "mks" << std::endl;
}

void TestAddRemoveTime(size_t size, BinaryTree<int>& tree) {
    double avg_ar_time = 0;
    for (size_t i = 0; i < 1000; ++i) {
        avg_ar_time += MeasureTime([&]() {
            tree.erase(lcg());
            tree.insert(lcg());
        });
    }

    avg_ar_time /= 2000;
    std::cout << "Average time for adding/deleting in tree: " << avg_ar_time << "mks" << std::endl;
}

void TestSearchVector(size_t size, std::vector<int>& vector) {
    double avg_s_v_time = 0;
    for (size_t i = 0; i < 1000; ++i) {
        avg_s_v_time += MeasureTime([&]() {
            std::find(vector.begin(), vector.end(), lcg()) != vector.end();
        });
    }

    avg_s_v_time /= 1000;
    std::cout << "Average time for searching in vector: " << avg_s_v_time << "mks" << std::endl;
}

void TestFillVector(size_t size, std::vector<int>& vector) {
    double avg_f_v_time = MeasureTime([&]() {
        for (size_t i = 0; i < size; ++i) {
            vector[i] = lcg();
        }
    });

    avg_f_v_time /= 1000;
    std::cout << "Average filling vector time: " << avg_f_v_time << "mks" << std::endl;
}

void TestAddRemoveVector(size_t size, std::vector<int>& vector) {
    double avg_ar_v_time = 0;
    for (size_t i = 0; i < 1000; ++i) {
        avg_ar_v_time += MeasureTime([&]() {
            vector.erase(std::remove(vector.begin(), vector.end(), lcg()), vector.end());
            vector.push_back(lcg());
            });
    }

    avg_ar_v_time /= 2000;
    std::cout << "Average time for adding/deleting in vector: " << avg_ar_v_time << "mks" << std::endl;
}