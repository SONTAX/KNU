#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;
/**
* A single node of tree
*/
template<typename T>
struct TreeNode {
	T value;	/**< Value stored in this node */
	TreeNode<T>* left;	/**< Pointer to the left child, can be epmty (nullptr) if node hasn`t left child */
	TreeNode<T>* right;	/**< Pointer to the right child, can be epmty (nullptr) if node hasn`t right child */
};
/**
* Simple binary tree
*/
template<typename T>
struct Tree {
	string output = "";	/**< String which containes output information */
	TreeNode<T>* root;	/**< Pointer to the tree root, can be epmty (nullptr) if tree is empty */
	TreeNode<T>* found_node;	/**< Pointer to found root */
	/**
	* Build the full binary tree with specified height and inputed by user values
	* \param h height of the tree to be built
	* \return pointer to the tree root
	*/
	TreeNode<T>* BuildTree(size_t h);
	/**
	* Build the full binary tree with specified height and random values in range [0, 10]
	* \param h height of the tree to be built
	* \return pointer to the tree root
	*/
	TreeNode<T>* BuildRandomTree(size_t h);
	/**
	* Recursive function which writes all tree nodes to the <output> in-order (left child, root, right child)
	*/
	void PrintTreeAsTree(TreeNode<T>* root, int level);
	/**
	* Recursive function which writes all tree nodes to the <output> in tree form
	*/
	void PrintTreeInOrder(TreeNode<T>* root);
	/**
	* Function that returns the <output> which containes tree in string form
	*/
	string Output();
	/**
	* Build the binary search tree with specified number of random values in range [0, 10]
	* \param count number of tree nodes
	* \return pointer to the tree root
	*/
	TreeNode<T>* BuildRandomBST(int count);
	/**
	* Build the binary search tree with specified number of values inputed by user
	* \param count number of tree nodes
	* \return pointer to the tree root
	*/
	TreeNode<T>* BuildBST(int count);
	/**
	* Finds and deletes node with specified value (his children also are deleted)
	*
	* \param val a value to be deleted
	* \param rt pointer to the tree root
	*/
	TreeNode<T>* DeleteByValue(T val, TreeNode<T>* rt);
	/**
	* Deletes node and all his children with specified pointer
	*
	* \param rt pointer to the tree root
	* \param found_node pointer to node to be deleted
	* \warning First you need to find pointer to deleted node
	*/
	TreeNode<T>* DeleteByAdress(TreeNode<T>* rt, TreeNode<T>* found_node);
	/**
	* Function that searches value in the tree if it exists writes pointer to it in <found_node> and returns true or returns false if it doesn`t exist
	*
	* \param val a value to be found
	* \param r00t pointer to the tree root
	*/
	bool Find(T val, TreeNode<T>* r00t);
	/**
	* \brief Add value to the tree
	*
	* Creates a new node containing this value, inserts it to the proper place (according to the binary search tree rules)
	*
	* \param val a value to be added
	* \param r00t pointer to the tree root
	*/
	TreeNode<T>* SearchInsert(TreeNode<T>* r00t, T val);
};

#include "Tree.hxx"

#endif 