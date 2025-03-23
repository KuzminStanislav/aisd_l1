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

size_t TestFillTime(size_t size, size_t attemps) {
    if (attemps == 0) {
        return 0;
    }

    size_t fill_time = 0;
    for (size_t i = 1; i <= attemps; ++i) {
        BinaryTree<int> tree;
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t j = 1; j <= size; ++j) {
            int item = static_cast<int>(lcg());
            tree.insert(item);
        }

        auto end = std::chrono::high_resolution_clock::now();
        fill_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    return fill_time / attemps;
}

size_t TestSearchTime(size_t size, size_t attemps) {
    if (attemps == 0) {
        return 0;
    }

    size_t search_time = 0;
    for (size_t i = 0; i < attemps; ++i) {
        BinaryTree<int> tree;
        std::vector<int> vector;

        for (size_t j = 0; j < size; ++j) {
            int item = static_cast<int>(lcg());
            tree.insert(item);
            vector.push_back(item);
        }

        int search_element = vector[lcg() % vector.size()];
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();

        search_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    return search_time / attemps;
}

size_t TestAddTime(size_t size, size_t attemps) {
    if (attemps == 0) {
        return 0;
    }

    size_t add_time = 0;

    for (size_t i = 0; i < attemps; ++i) {
        BinaryTree<int> tree;
        for (size_t j = 0; j < size; ++j) {
            int item = static_cast<int>(lcg());
            tree.insert(item);
        }
    
        int add_element = static_cast<int>(lcg());

        auto start = std::chrono::steady_clock::now();
        tree.insert(add_element);
        auto end = std::chrono::steady_clock::now();

        add_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    return add_time / attemps;
}

size_t TestEraseTime(size_t size, size_t attemps) {
    if (attemps == 0) {
        return 0;
    }

    size_t erase_time = 0;

    for (size_t i = 0; i < attemps; ++i) {
        BinaryTree<int> tree;
        std::vector<int> vector;

        for (size_t j = 0; j < size; ++j) {
            int item = static_cast<int>(lcg());
            tree.insert(item);
            vector.push_back(item);
        }

        int erase_element = vector[lcg() % vector.size()];

        auto start = std::chrono::steady_clock::now();
        tree.erase(erase_element);
        auto end = std::chrono::steady_clock::now();

        erase_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    return erase_time / attemps;
}

size_t TestVecFillTime(size_t size, size_t attemps) {
    if (attemps == 0) {
        return 0;
    }

    size_t fill_time = 0;
    for (size_t i = 1; i <= attemps; ++i) {
        std::vector<int> vector;
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t j = 1; j <= size; ++j) {
            int item = static_cast<int>(lcg());
            vector.push_back(item);
        }

        auto end = std::chrono::high_resolution_clock::now();
        fill_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    return fill_time / attemps;
}

size_t TestVecSearchTime(size_t size, size_t attemps) {
    if (attemps == 0) {
        return 0;
    }

    size_t search_time = 0;
    for (size_t i = 0; i < attemps; ++i) {
        std::vector<int> vector;

        for (size_t j = 0; j < size; ++j) {
            int item = static_cast<int>(lcg());
            vector.push_back(item);
        }

        int search_element = vector[lcg() % vector.size()];
        auto start = std::chrono::high_resolution_clock::now();
        for (auto elem : vector) {
            if (elem == search_element) {
                break;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();

        search_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    return search_time / attemps;
}

size_t TestVecAddTime(size_t size, size_t attemps) {
    if (attemps == 0) {
        return 0;
    }

    size_t add_time = 0;

    for (size_t i = 0; i < attemps; ++i) {
        std::vector<int> vector;
        for (size_t j = 0; j < size; ++j) {
            int item = static_cast<int>(lcg());
            vector.push_back(item);
        }

        int add_element = static_cast<int>(lcg());

        auto start = std::chrono::steady_clock::now();
        vector.push_back(add_element);
        auto end = std::chrono::steady_clock::now();

        add_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    return add_time / attemps;
}

size_t TestVecEraseTime(size_t size, size_t attemps) {
    if (attemps == 0) {
        return 0;
    }

    size_t erase_time = 0;

    for (size_t i = 0; i < attemps; ++i) {
        std::vector<int> vector;

        for (size_t j = 0; j < size; ++j) {
            int item = static_cast<int>(lcg());
            vector.push_back(item);
        }

        size_t erase_element = lcg() % vector.size();

        auto start = std::chrono::steady_clock::now();
        vector.erase(vector.begin() + erase_element);
        auto end = std::chrono::steady_clock::now();

        erase_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    return erase_time / attemps;
}