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
    int height;

    Node(const T& value): data(value), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class BinaryTree {
private:
    std::unique_ptr<Node> root;

    void copy_helper(Node* current, const Node* other) {
        if (other) {
            if (other->left) {
                current->left = std::make_unique<Node>(other->left->data);
                copy_helper(current->left.get(), other->left.get());
            }

            if (other->right) {
                current->right = std::make_unique<Node>(other->right->data);
                copy_helper(current->right.get(), other->right.get());
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

    bool insert_helper(const T& key, std::unique_ptr<Node>& node) {
        if (node == nullptr) {
            node = std::make_unique<Node>(key);
            return true;
        }

        if (key < node->data) {
            return insert_helper(key, node->left);
        }

        else if (key > node->data) {
            return insert_helper(key, node->right);
        }
        return false;
    }

    Node* contain_helper(const T& key, const Node* node) const {
        if (node == nullptr || key == node->data) {
            return const_cast<Node*>(node);
        }

        if (key < node->data) {
            return contain_helper(key, node->left.get());
        }

        else {
            return contain_helper(key, node->right.get());
        }
    }

    bool erase_helper(const T& key, std::unique_ptr<Node>& node) {
        if (node == nullptr) {
            return false;
        }

        if (key < node->data) {
            return erase_helper(key, node->left);
        }

        else if (key > node->data) {
            return erase_helper(key, node->right);
        }

        else {
            if (node->left == nullptr) {
                node = std::move(node->right);
            }

            else if (node->right == nullptr) {
                node = std::move(node->left);
            }

            else {
                Node* chd_node = minimum(node->right.get());
                node->data = chd_node->data;
                erase_helper(chd_node->data, node->right);
            }
            return true;
        }
    }

    Node* minimum(const Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }

        while (node->left != nullptr) {
            node = node->left.get();
        }
        return const_cast<Node*>(node);
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
                copy_helper(root.get(), other.root.get());
            }
        }
        return *this;
    }

    void print() const {
        print_helper(root.get());
        std::cout << std::endl;
    }

    bool insert(const T& key) {
        return insert_helper(key, root);
    }

    bool contains(const T& key) {
        return contain_helper(key, root.get()) != nullptr;
    }

    bool erase(const T& key) {
        return erase_helper(key, root);
    }

    //AVL-Tree(balanced)

    int get_height(const Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int balance_factor(const Node* node) const {
        return get_height(node->left.get()) - get_height(node->right.get());
    }

    void update_height(Node* node) {
        if (node == nullptr) {
            return;
        }
        node->height = std::max(height(node->left.get()), height(node->right.get())) + 1;
    }

    std::unique_ptr<Node> rotate_left(std::unique_ptr<Node>& node) {
        std::unique_ptr<Node> new_root = std::move(node->right);
        node->rigth = std::move(new_root->left);
        new_root->left = std::move(node);
        update_height(node.get());
        update_height(new_root.get());
        return new_root;
    }

    std::unique_ptr<Node> rotate_right(std::unique_ptr<Node>& node) {
        std::unique_ptr<Node> new_root = std::move(node->left);
        node->left = std::move(new_root->right);
        new_root->right = std::move(node);
        update_height(node.get());
        update_height(new_root.get());
        return new_root;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}