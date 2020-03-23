/*! \file
 *
 * Definitions for the nTrix class. \n
 * Programmer: Noah Klein \n
 * Class: CS5201 \n
 * Assignment: Homework 5 \n
 */

#ifndef NTRIX_H
#define NTRIX_H

#include <iostream>
#include "nVect.h"

template <typename T>
class nTrix
{
	private:
		unsigned short m_row;
		unsigned short m_col;
		T** m_matrix;

	public:

		// Essential //

		nTrix();
		nTrix(const std::initializer_list<std::initializer_list<T>> grid);
		nTrix(const short num_rows, const short num_cols);
    nTrix(const nVect<T>& rhs);
		nTrix(const nTrix<T>& rhs);
		nTrix<T>& operator=(const nTrix<T>& rhs);
		~nTrix();

		// Accessors //

		unsigned short rows() const;
		unsigned short cols() const;

		// Mutators //

		T& operator()(const int row_index, const int col_index);
    nTrix<T> operator+(const nTrix<T>& rhs) const;
    nTrix<T> operator-(const nTrix<T>& rhs) const;
    nTrix<T> operator-() const;
    nTrix<T> operator*(const nTrix<T>& rhs) const;
    nTrix<T> operator*(const nVect<T>& rhs) const;

		// Friend //
		template <typename U>
		friend std::ostream& operator<<(std::ostream& out, const nTrix<U>& rhs);

    // template <typename U>
    // friend nTrix<U> operator*(const nTrix<U>& lhs, const float scalar);
};

// Extras //

template <typename T>
std::ostream& operator<<(std::ostream& out, const nTrix<T>& rhs);

template <typename T>
nTrix<T> operator*(const nTrix<T>& lhs, const float scalar);

template <typename T>
nTrix<T> operator*(const nVect<T>& lhs, const nTrix<T>& rhs);

#include "nTrix.hpp"
#endif
