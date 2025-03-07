#include <iostream>

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x * 24631) % 116640;
    return x;
}

template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
    int height;

    Node(const T& value): data(value), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class BinaryTree {
private:
    Node* root;

    void destroy_tree(Node* node) {
        if (node) {
            destroy_tree(node->left);
            destroy_tree(node->right);
            delete node;
        }
    }

    Node* copy_helper(const Node* other) {
        if (other == nullptr) {
            return nullptr;
        }

        Node* new_node = new Node(other->data);
        new_node->left = copy_helper(other->left);
        new_node->right = copy_helper(other->right);
        return new_node;
    }

    void print_helper(const Node* node) const {
        if (node) {
            print_helper(node->left);
            std::cout << node->data << " ";
            print_helper(node->right);
        }
    }

    bool insert_helper(const T& key, Node*& node) {
        if (node == nullptr) {
            node =  new Node(key);
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
            return node;
        }

        if (key < node->data) {
            return contain_helper(key, node->left);
        }

        else {
            return contain_helper(key, node->right);
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
                Node* old = node;
                node = node->right;
                delete old;
            }

            else if (node->right == nullptr) {
                Node* old = node;
                node = node->left;
                delete old;
            }

            else {
                Node* chd_node = minimum(node->right);
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
        return node;
    }

public:
    BinaryTree() : root(nullptr) {};

    ~BinaryTree() {
        destroy_tree(root);
    }

    BinaryTree(const BinaryTree& other) {
        if (other.root) {
            root = copy_helper(other.root);
        }
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            destroy_tree(root);
            if (other.root) {
                root = copy_helper(other.root);
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