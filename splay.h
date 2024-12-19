#pragma once
#include <iostream>
#include <string>

template <typename T>
class SplayTree
{
private:
    // Node structure definition
    class Node
    {
    public:
        T key;
        Node* left;
        Node* right;
        time_t time;

        Node(const T& value) : key(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* splayHelper(Node* subtreeRoot, const T& key);
    Node* rightRotate(Node* x);
    Node* leftRotate(Node* x);

public:
    SplayTree() : root(nullptr) {}
    ~SplayTree();

    void splay(const T& key);
    void insert(const T& key);
    void remove(const T& key);

    // Inorder traversal declarations
    void inorder(std::ostream& out) const;              // Full traversal
    void inorder(std::ostream& out, int maxDepth) const; // Depth-limited traversal
    void access(const T& key);

private:
    void inorderAux(std::ostream& out, Node* subtreeRoot, int currentDepth, int maxDepth) const;
    void deleteTree(Node* subtreeRoot);
};

// Implementation

/// Destructor
template <typename T>
SplayTree<T>::~SplayTree()
{
    deleteTree(root);
}

template <typename T>
void SplayTree<T>::deleteTree(Node* subtreeRoot)
{
    if (subtreeRoot)
    {
        deleteTree(subtreeRoot->left);
        deleteTree(subtreeRoot->right);
        delete subtreeRoot;
    }
}

// Right rotation
template <typename T>
typename SplayTree<T>::Node* SplayTree<T>::rightRotate(Node* x)
{
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Left rotation
template <typename T>
typename SplayTree<T>::Node* SplayTree<T>::leftRotate(Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay helper function
template <typename T>
typename SplayTree<T>::Node* SplayTree<T>::splayHelper(Node* subtreeRoot, const T& key)
{
    if (!subtreeRoot || subtreeRoot->key == key)
        return subtreeRoot;

    if (subtreeRoot->key > key)
    {
        if (!subtreeRoot->left)
            return subtreeRoot;

        if (subtreeRoot->left->key > key)
        {
            subtreeRoot->left->left = splayHelper(subtreeRoot->left->left, key);
            subtreeRoot = rightRotate(subtreeRoot);
        }
        else if (subtreeRoot->left->key < key)
        {
            subtreeRoot->left->right = splayHelper(subtreeRoot->left->right, key);

            if (subtreeRoot->left->right)
                subtreeRoot->left = leftRotate(subtreeRoot->left);
        }

        return subtreeRoot->left ? rightRotate(subtreeRoot) : subtreeRoot;
    }
    else
    {
        if (!subtreeRoot->right)
            return subtreeRoot;

        if (subtreeRoot->right->key > key)
        {
            subtreeRoot->right->left = splayHelper(subtreeRoot->right->left, key);

            if (subtreeRoot->right->left)
                subtreeRoot->right = rightRotate(subtreeRoot->right);
        }
        else if (subtreeRoot->right->key < key)
        {
            subtreeRoot->right->right = splayHelper(subtreeRoot->right->right, key);
            subtreeRoot = leftRotate(subtreeRoot);
        }

        return subtreeRoot->right ? leftRotate(subtreeRoot) : subtreeRoot;
    }
}

// Splay operation
template <typename T>
void SplayTree<T>::splay(const T& key)
{
    if (!root)
        return;

    root = splayHelper(root, key);
}

template <typename T>
void SplayTree<T>::access(const T& key)
{
    if (!root)
        return;

    root = splayHelper(root, key);
    root->time = time(NULL);
}

// Insert operation
template <typename T>
void SplayTree<T>::insert(const T& key)
{

    if (!root)
    {
        root = new Node(key);
        root->time = time(NULL);
        return;
    }


    root = splayHelper(root, key);
    root->time = time(NULL);
    if (root->key == key)
        return;

    Node* newNode = new Node(key);
    newNode->time =time(NULL);

    if (root->key > key)
    {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    }
    else
    {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }

    root = newNode;
}

// Remove operation
template <typename T>
void SplayTree<T>::remove(const T& key)
{
    if (!root)
        return;

    root = splayHelper(root, key);
    system("pause");
    root->time = time(NULL);
    if (root->key != key)
        return;

    Node* temp;

    if (!root->left)
    {
        temp = root;
        root = root->right;
    }
    else
    {
        temp = root;
        root = splayHelper(root->left, key);
        root->right = temp->right;
    }
    system("pause");
    root->time=time(NULL);
    delete temp;
}

// Depth-aware inorder traversal
template <typename T>
void SplayTree<T>::inorder(std::ostream& out) const
{
    inorder(out, -1); // Default to full traversal
}

template <typename T>
void SplayTree<T>::inorder(std::ostream& out, int maxDepth) const
{
    inorderAux(out, root, 0, maxDepth);
    out << std::endl;
}

template <typename T>
void SplayTree<T>::inorderAux(std::ostream& out, Node* subtreeRoot, int currentDepth, int maxDepth) const
{
    if (subtreeRoot == nullptr || (maxDepth >= 0 && currentDepth >= maxDepth))
        return;

    inorderAux(out, subtreeRoot->left, currentDepth + 1, maxDepth);

    out << subtreeRoot->key << "\t" << subtreeRoot->time << std::endl;

    inorderAux(out, subtreeRoot->right, currentDepth + 1, maxDepth);
}