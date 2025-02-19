#include <iostream>
#include <memory>

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x * 24631) % 116640;
    return x;
}


template <typename T>
struct Node {
    T data;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(const T& value): data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree {
private:
    std::unique_ptr<Node> root;

    void copy_recursive(Node* current, const Node* other) {
        if (other) {
            if (other->left) {
                current->left = std::make_unique<Node>(other->left->data);
                copy_recursive(current->left.get(), other->left.get());
            }

            if (other->right) {
                current->right = std::make_unique<Node>(other->right->data);
                copy_recursive(current->right.get(), other->right.get());
            }
        }
    }

public:
    BinaryTree() : root(nullptr) {};

    ~BinaryTree() {
        root.reset();
    }

    BinaryTree(const BinaryTree& other) {
        if (other.root) {
            root = std::make_unique<Node>(other.root->data);
            copy_recursive(root.get(), other.root.get());
        }
    }


};

int main()
{
    std::cout << "Hello World!\n";
}