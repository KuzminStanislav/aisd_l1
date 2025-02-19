#include <iostream>

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x * 24631) % 116640;
    return x;
}

struct Node {
    T data;
    Node* left;
    Node* right;

    Node(const T& value): data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree {
private:
    Node* root;
};

int main()
{
    std::cout << "Hello World!\n";
}