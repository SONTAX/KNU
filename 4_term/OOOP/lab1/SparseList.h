#ifndef SPARSELIST_H_
#define SPARSELIST_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;
/**
* A single node of sparse doubly linked list
*/
template<typename T>
struct Node {
	size_t index;	/**< Index in list for nodes which have not-zero values  */
	T value;	/**< Value stored in this node */
	Node<T>* prev = nullptr;	/**< Pointer to the previous node in the list, can be epmty (nullptr) for the first node */
	Node<T>* next = nullptr;	/**< Pointer to the next node in the list, can be epmty (nullptr) for the last node */
};
/**
* A sparse list optimal to use when we have a lot of zero values
*/
template<typename T>
struct SparseList {
	Node<T>* pbeg = nullptr;	/**< Pointer to the first node in the list, can be epmty (nullptr) if the list is empty or consists of zero values */
	Node<T>* pend = nullptr;	/**< Pointer to the first node in the list, can be epmty (nullptr) if the list is empty or consists of zero values */
	size_t list_size = 0;	/**< Number of nodes in the list */

	bool was_zero = false;	/**< Logic value which shows is at least one zero value in the node */
	size_t zero_index;	/**< Index for first node with zero value  */

	/**
	* \brief Add value to the end of list
	* 
	* Creates a new node containing this value, inserts it at the end of list.
	* 
	* \param value a value to be added
	* \post List size is increased by 1.
	*/
	void Add(T val);
	/**
	* Returns the full list, including zero values, as a string
	*/
	string PrintAll();
	/**
	* \brief Creates new list
	*
	* Creates new list filled by values inputed by user with set by user list size
	*
	* \param lenth new list size
	*/
	void GetList(size_t lenth);
	/**
	* Search for value in the list
	* 
	* \param val a value to be searched
	* \return index for the first entry of searchen value to the list
	* \throw return -1 if there is no such value in the list
	*/
	int GetIndex(T val);
	/**
	* Returns value with specified index
	*
	* \param ind index of value in the list
	* \throw return -1 if index is too large (greater or equal to list size)
	*/
	T GetValue(size_t ind);
	/**
	* \brief Creates new list with random values
	*
	* Creates new list filled by random nubmers [0; 5] with set by user list size
	*
	* \param lenth new list size
	*/
	void GetRandomList(size_t lenth);
	/**
	* Delets all list
	* 
	* \post List size sets equal 0.
	*/
	void DeleteList();
};

#include "SparseList.hxx"

#endif