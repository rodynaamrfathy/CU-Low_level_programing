#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

class BinaryTreeNode {
public:
    int n;
    BinaryTreeNode* parent;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    // Constructor
    BinaryTreeNode(int value, BinaryTreeNode* parent = nullptr, BinaryTreeNode* left = nullptr, BinaryTreeNode* right = nullptr) : 
        n(value), parent(parent), left(left), right(right) {}
};

class BinaryTree {
public:
    BinaryTreeNode* root;

    // Constructor
    BinaryTree(int rootValue) {
        root = new BinaryTreeNode(rootValue);
    }
};


class HeapNode{
	public:
	// key is for priority queues
	int key;
	// can be templete variable if it is used for priority queues but for now just int
	int value;
};

class Heap {
public:
    HeapNode** array;
    int arraySize;
	int heapSize;

    // Constructor
   

    // Heapify a subtree rooted with node i
    virtual void heapify(int i) = 0;

    // Build the heap
    virtual void buildHeap() = 0;

    // Heap sort
    virtual void heapSort() = 0;
};

/* Original code from http://stackoverflow.com/a/13755911/5184480 */

// Utility function to print binary tree
static int print_t(const BinaryTreeNode* tree, int offset, int depth, char **s)
{
	char b[6];
	int width, left, right, is_left, i;

	if (!tree)
		return 0;
	is_left = (tree->parent && tree->parent->left == tree);
	width = sprintf(b, "(%03d)", tree->n);
	left = print_t(tree->left, offset, depth + 1, s);
	right = print_t(tree->right, offset + left + width, depth + 1, s);
	for (i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];
	if (depth && is_left)
	{
		for (i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	else if (depth && !is_left)
	{
		for (i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	return left + width + right;
}

// Utility function to measure the height of a binary tree
static size_t _height(const BinaryTreeNode* tree)
{
	size_t height_l;
	size_t height_r;

	height_l = tree->left ? 1 + _height(tree->left) : 0;
	height_r = tree->right ? 1 + _height(tree->right) : 0;
	return (height_l > height_r ? height_l : height_r);
}



// Function to print a binary tree
void binary_tree_print(const BinaryTreeNode* tree)
{
	char **s;
	size_t height, i, j;

	if (!tree)
		return;
	height = _height(tree);
	s = new char*[height + 1];
	if (!s)
		return;
	for (i = 0; i < height + 1; i++)
	{
		s[i] = new char[255];
		if (!s[i])
			return;
		std::memset(s[i], 32, 255);
	}
	print_t(tree, 0, 0, s);
	for (i = 0; i < height + 1; i++)
	{
		for (j = 254; j > 1; --j)
		{
			if (s[i][j] != ' ')
				break;
			s[i][j] = '\0';
		}
		std::cout << s[i] << std::endl;
		delete[] s[i];
	}
	delete[] s;
}

#endif /* BINARY_TREE_H */
