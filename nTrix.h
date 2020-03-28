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
#include <cmath>
#include "nVect.h"

template <typename T>
class nTrix
{
	private:
		short m_row;
	  short m_col;
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

		short rows() const;
		short cols() const;
		const T& operator()(const int row_index, const int col_index) const;


		// Mutators //

		T& operator()(const int row_index, const int col_index);
    nTrix<T> operator+(const nTrix<T>& rhs) const;
    nTrix<T> operator-(const nTrix<T>& rhs) const;
    nTrix<T> operator-() const;
    nTrix<T> operator*(const nTrix<T>& rhs) const;
    nTrix<T> operator*(const nVect<T>& rhs) const;
		void clear(nTrix<T>& rhs);


		// Friend //
		template <typename U>
		friend std::ostream& operator<<(std::ostream& out, const nTrix<U>& rhs);

		template <typename U>
		friend std::istream& operator>>(std::istream& in, const nTrix<U>& rhs);
};

// Extras //

template <typename T>
std::ostream& operator<<(std::ostream& out, const nTrix<T>& rhs);

template <typename T>
std::istream& operator>>(std::istream& in, const nTrix<T>& rhs);

template <typename T>
nTrix<T> operator*(const nTrix<T>& lhs, const float scalar);

template <typename T>
nTrix<T> operator*(const nVect<T>& lhs, const nTrix<T>& rhs);

template <typename T>
float frobenius(const nTrix<T>& rhs);

template <typename T>
nTrix<float> invert(const nTrix<T>& rhs);

nTrix<float> r_invert(const double I, nTrix<float> P, const nTrix<float> A);

#include "nTrix.hpp"
#endif