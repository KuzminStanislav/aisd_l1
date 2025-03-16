#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "tree.cpp"
#include "tests.cpp"

int main() {
    //time tests

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    size_t sizes[] = {1000, 10000, 100000};

    for (size_t i = 0; i < sizeof(sizes) / sizeof(sizes[0]); ++i) {
        size_t size = sizes[i];
        std::cout << "Size: " << size << std::endl;

        BinaryTree<int> tree;
        TestFillTime(size, tree);
        TestSearchTime(size, tree);
        TestAddRemoveTime(size, tree);

        std::vector<int> vector(size);
        TestSearchVector(size, vector);
        TestFillVector(size, vector);
        TestAddRemoveVector(size, vector);
        std::cout << "-----------" << std::endl << std::endl;
    }
    return 0;
}
