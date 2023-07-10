/**
 * @file splayTree.hpp
 * @author Ryan Butler (rbutler@g.hmc.edu)
 * @brief Implementation of a splay tree with no parent pointer
 * @version 0.1
 * @date 2023-07-08
 * @note Full documentation is in README.md
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SPLAY_TREE_HPP_INCLUDED
#define SPLAY_TREE_HPP_INCLUDED

#include <vector>
#include <iterator>
#include <tuple>

template <typename key_t, typename value_t>
class SplayTree {
  private:
    class const_iterator;
    struct Node {
        key_t key_;
        value_t value_;
        Node *right_;
        Node *left_;

        Node(key_t key, value_t value);
    };

    // Data
    Node* root_;
    size_t size_;

    // Helper Functions:
    void destructorHelper(Node*& node);
    void insertHelper(const key_t &key, const value_t &value, Node*& node, std::vector<Node *> &path);
    const const_iterator searchHelper(const key_t &key, Node*& node, std::vector<Node*>& path);
    void printTree(Node* tree, std::ostream& out) const;
    void getMaxPath(Node *node, std::vector<Node *>& path) const;

    // Splay Functions
    void splay(std::vector<Node *> &path);
    void rotateRight(Node *&node);
    void rotateLeft(Node *&node);
    void cleanGreatGP(std::vector<Node *> &path, size_t newNodeInd,Node*& newNode, const key_t& newKey);


public:

    // Constructors
    SplayTree();
    ~SplayTree();
    SplayTree(const SplayTree &other) = default;
    SplayTree &operator=(const SplayTree &other) = default;

    // Interface Functions
    void insert(const key_t& key, const value_t& value);
    void remove(const key_t &key);
    bool exists(const key_t &key);
    const const_iterator find(const key_t &key);
    size_t size() const;

    // Iterator functions
    const_iterator begin() const;
    const_iterator end() const;

    // Other functions
    void print(std::ostream &out) const;
    value_t& operator[](const key_t &key);

  private:
    class const_iterator {
        friend class SplayTree;

    private:
        std::vector<Node *> stack_;
        void pushToMin(Node *tree);

    public:

        // Required for std::iterator
        using value_type = std::tuple<key_t, value_t>;
        using reference = const value_type&;
        using pointer = const value_type*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() = default;
        const_iterator(Node *node, bool push = true);
        const_iterator(const const_iterator &other) = delete;
        const_iterator &operator=(const const_iterator &other) = default;
        ~const_iterator() = default;

        value_type operator*() const;
        const_iterator &operator++();
        pointer operator->() const;
        bool operator==(const const_iterator &other) const;
        bool operator!=(const const_iterator &other) const;
        
    };
};

template <typename key_t,typename value_t>
std::ostream &operator<<(std::ostream& out, const SplayTree<key_t, value_t> &splaytree);

#include "splayTree-private.hpp"

#endif // SPLAY_TREE_HPP_INCLUDED