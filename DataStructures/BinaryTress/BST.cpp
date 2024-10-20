#include "BinaryTree.h"
#include <queue>
#include <iostream>

using namespace std;

class BinarySearchTree : public BinaryTree
{
public:
    BinaryTreeNode* insert(int value);
    void delete(BinaryTreeNode* &node);
    void BreadthFirstTraversal();
    void InOrderTraversal();
    void PreOrderTraversal();
    void PostOrderTraversal();
    search (BinaryTreeNode& el)
};

// In-Order Traversal (left, root, right)
void BinarySearchTree::InOrderTraversal() {
    InOrderTraversal(root);
    cout << endl;
}

void BinarySearchTree::InOrderTraversal(BinaryTreeNode* node) {
    if (node != nullptr) {
        InOrderTraversal(node->left);
        cout << node->n << " ";
        InOrderTraversal(node->right);
    }
}

// Pre-Order Traversal (root, left, right)
void BinarySearchTree::PreOrderTraversal() {
    PreOrderTraversal(root);
    cout << endl;
}

void BinarySearchTree::PreOrderTraversal(BinaryTreeNode* node) {
    if (node != nullptr) {
        cout << node->n << " ";
        PreOrderTraversal(node->left);
        PreOrderTraversal(node->right);
    }
}

// Post-Order Traversal (left, right, root)
void BinarySearchTree::PostOrderTraversal() {
    PostOrderTraversal(root);
    cout << endl;
}

void BinarySearchTree::PostOrderTraversal(BinaryTreeNode* node) {
    if (node != nullptr) {
        PostOrderTraversal(node->left);
        PostOrderTraversal(node->right);
        cout << node->n << " ";
    }
}

BinaryTreeNode* BinarySearchTree:: search (BinaryTreeNode& el) {
    BinaryTreeNode* p = root;
    while (p != 0){
        if (el == p->key)
            return &p->key;
        else if (el < p->key)
            p = p->left;
        else
            p = p->right;
        }
        return 0;
}

BinaryTreeNode* BinarySearchTree::insert(int value)
{
    if (root == nullptr)
    {
        root = new BinaryTreeNode(value);
        return root;
    }

    BinaryTreeNode* p = root, * prev = root;
    while (p != nullptr)
    {
        prev = p;
        if (p->n < value)
            p = p->right;
        else
            p = p->left;
    }

    if (prev->n < value)
    {
        prev->right = new BinaryTreeNode(value);
        return prev->right;
    }
    else
    {
        prev->left = new BinaryTreeNode(value);
        return prev->left;
    }
}

void BinarySearchTree::BreadthFirstTraversal()
{
    queue<BinaryTreeNode*> q;
    BinaryTreeNode* p = root;
    if (p != nullptr)
    {
        q.push(p);
        while (!q.empty())
        {
            p = q.front();
            q.pop();
            cout << p->n << " ";

            if (p->left != nullptr)
                q.push(p->left);
            if (p->right != nullptr)
                q.push(p->right);
        }
    }
    cout << endl;
}

void BinarySearchTree::deleteNode(BinaryTreeNode*& node) {
    if (node == nullptr)
        return;

    BinaryTreeNode *prev, *tmp = node;
    
    // If the node to be deleted has no right child, replace it with its left child.
    if (node->right == nullptr)
        node = node->left;
    // If the node to be deleted has no left child, replace it with its right child.
    else if (node->left == nullptr)
        node = node->right;
    // If the node to be deleted has two children
    else {
        prev = node;
        tmp = node->left;

        // Find the rightmost node in the left subtree (inorder predecessor)
        while (tmp->right != nullptr) {
            prev = tmp;
            tmp = tmp->right;
        }

        // Replace the value of the node to be deleted with the inorder predecessor's value
        node->n = tmp->n;

        // Adjust the pointers to remove the inorder predecessor node
        if (prev == node) {
            // If the left subtree does not have a right child
            node->left = tmp->left;
        } else {
            // If the inorder predecessor has a left child
            prev->right = tmp->left;
        }
    }

    // Delete the inorder predecessor node
    delete tmp;
}
