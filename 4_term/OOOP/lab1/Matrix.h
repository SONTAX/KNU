#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;
/**
* Sparse matrix stored as "Dictionary of keys"
*/
struct Matrix {

	vector<int> val;	/**< Vector which stores not-zero values */
	vector<int> row;	/**< Vector which stores row indexes of not-zero values */
	vector<int> col;	/**< Vector which stores column indexes of not-zero values */
	int dimension;	/**< Matrix dimension */

	bool was_zero = false;	/**< Logic value which shows is at least one zero value in the matrix */
	int zero_row;	/**< Row index for first zero value*/
	int zero_col;	/**< Column index for first zero value*/
	/**
	* Function that returns matrix as string
	*/
	string PrintMatrix() const;
	/**
	* Create new matrix with specified dimension and filled with inputed by user values
	* \param n matrix dimension
	*/
	void GetMatrix(int n);
	/**
	* Create new matrix with specified dimension and filled with random values from range [0-4]
	* \param n matrix dimension
	*/
	void GetRandomMatrix(int n);
	/**
	* Returns value with specified indexes
	* 
	* \param rw row index
	* \param cl column index
	* \throw "Indexes are more then dimension!" (if inputed indexes are more or equal to dimension)
	*/
	void GetByIndex(int rw, int cl);
	/**
	* Search for value in the matrix
	* \param value value to be searched
	* \return indexes for the first entry of searchen value to the matrix
	* \throw "There are no indexes for such value!" (if inputed doesn`t exist in matrix)
	*/
	void GetByValue(int value);
	/**
	* Addition matrix with random values and same dimension to current matrix 
	*/
	void Sum();
	/**
	* Multiplication matrix with random values and same dimension by current matrix
	*/
	void MultiplicationByMatrix();
	/**
	* Multiplication current matrix by vector with random values and same length
	*/
	void MultiplicationByVector();
	/**
	* Transponation of current matrix
	*/
	void Transponation();
};

#endif 