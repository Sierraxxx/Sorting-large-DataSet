#pragma once
#include <string>
#include <vector>
#include <algorithm>

/**
 * AVL Tree (self-balancing BST)
 * Insert: O(log n) per word — maintains balance factor in [-1, 0, 1]
 * Inorder traversal: O(n) — produces words in alphabetical order
 */

struct AVLNode {
    std::string key;
    AVLNode*    left;
    AVLNode*    right;
    int         height;

    explicit AVLNode(const std::string& k)
        : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLTree()  : root_(nullptr) {}
    ~AVLTree() { destroy(root_); }

    void insert(const std::string& key) {
        root_ = insert(root_, key);
    }

    // Returns words sorted alphabetically via inorder traversal
    std::vector<std::string> getSorted() const {
        std::vector<std::string> result;
        result.reserve(100001);
        inorder(root_, result);
        return result;
    }

private:
    AVLNode* root_;

    // ── Height helpers ───────────────────────────────────────
    int height(AVLNode* n) const { return n ? n->height : 0; }

    void updateHeight(AVLNode* n) {
        n->height = 1 + std::max(height(n->left), height(n->right));
    }

    int getBalance(AVLNode* n) const {
        return n ? height(n->left) - height(n->right) : 0;
    }

    // ── Rotations ────────────────────────────────────────────
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x  = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left  = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y  = x->right;
        AVLNode* T2 = y->left;
        y->left  = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // ── Rebalance after insert ────────────────────────────────
    AVLNode* rebalance(AVLNode* node, const std::string& key) {
        int balance = getBalance(node);

        // Left-Left
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Right-Right
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Left-Right
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right-Left
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // ── Recursive insert ─────────────────────────────────────
    AVLNode* insert(AVLNode* node, const std::string& key) {
        if (!node) return new AVLNode(key);

        if      (key < node->key) node->left  = insert(node->left,  key);
        else if (key > node->key) node->right = insert(node->right, key);
        else    return node; // duplicates are ignored

        updateHeight(node);
        return rebalance(node, key);
    }

    // ── Inorder traversal ────────────────────────────────────
    void inorder(AVLNode* node, std::vector<std::string>& out) const {
        if (!node) return;
        inorder(node->left,  out);
        out.push_back(node->key);
        inorder(node->right, out);
    }

    // ── Memory cleanup ───────────────────────────────────────
    void destroy(AVLNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};
