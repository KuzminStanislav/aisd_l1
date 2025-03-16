#pragma once
#include <iostream>

template <typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

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

    Node* contain_helper(const T& key, Node* node) const {
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

    bool erase_helper(const T& key, Node*& node) {
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

    Node* minimum(Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }

        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* maximum(Node* node) const {
        if (node == nullptr) {
            return nullptr;
        }

        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    size_t get_size(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + get_size(node->left) + get_size(node->right);
    }

    //AVL-Tree(balanced)

    int get_height(const Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int balance_factor(const Node* node) const {
        if (node == nullptr) {
            return 0;
        }

        return get_height(node->left) - get_height(node->right);
    }

    void update_height(Node* node) {
        if (node == nullptr) {
            return;
        }
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    Node* rotate_left(Node*& node) {
        Node* new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
        update_height(node);
        update_height(new_root);
        return new_root;
    }

    Node* rotate_right(Node*& node) {
        Node* new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
        update_height(node);
        update_height(new_root);
        return new_root;
    }

    Node* balance(Node*& node) {
        if (node == nullptr) {
            return node;
        }

        update_height(node);
        int bf = balance_factor(node);

        if (bf > 1) {
            if (balance_factor(node->left) >= 0) {
                return rotate_right(node);
            }

            else {
                node->left = rotate_left(node->left);
                return rotate_right(node);
            }
        }

        else if (bf < -1) {
            if (balance_factor(node->right) <= 0) {
                return rotate_left(node);
            }

            else {
                node->right = rotate_right(node->right);
                return rotate_left(node);
            }
        }
        return node;
    }

    Node* insert_balance(const T& key, Node*& node) {
        if (node == nullptr) {
            node = new Node(key);
        }
        else if (key < node->data) {
            node->left = insert_balance(key, node->left);
        }
        else if (key > node->data) {
            node->right = insert_balance(key, node->right);
        }
        else {
            return node;
        }
        return balance(node);
    }

    Node* erase_balance(const T& key, Node*& node) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->data) {
            node->left = erase_balance(key, node->left);
        }
        else if (key > node->data) {
            node->right = erase_balance(key, node->right);
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
                node->right = erase_balance(chd_node->data, node->right);
            }
        }
        return balance(node);
    }

    bool balanced_insert(const T& key) {
        root = insert_balance(root, key);
        return true;
    }

    bool balanced_erase(const T& key) {
        root = erase_balance(root, key);
        return true;
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
        return contain_helper(key, root) != nullptr;
    }

    bool erase(const T& key) {
        return erase_helper(key, root);
    }

    size_t size() const {
        return get_size(root);
    }
};