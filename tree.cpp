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

    void print_helper(const Node* node) const {
        if (node) {
            print_helper(node->left.get());
            std::cout << node->data << " ";
            print_helper(node->right.get());
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

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            root.reset();
            if (other.root) {
                root = std::make_unique<Node>(other.root->data);
                copy_recursive(root.get(), other.root.get());
            }
        }
        return *this;
    }

    void print() const {
        print_helper(root.get());
        std::cout << std::endl;
    }

    bool insert(const T& key, std::unique_ptr<Node>& node) {

    }
};

int main()
{
    std::cout << "Hello World!\n";
}