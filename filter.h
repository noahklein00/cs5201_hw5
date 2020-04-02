/*! \file
 *
 * Definitions for the filter base class. \n
 * Programmer: Noah Klein \n
 * Class: CS5201 \n
 * Assignment: Homework 5 \n
 */

#ifndef FILTER_H
#define FILTER_H
#include "nVect.h"

//! filter class.
/*!
 * This class is a base filter class that allows the user to specify derived
 * filter classes with () functionality.
 */
template <typename T>
class filter
{
  public:

    /*! \brief () operator
		 *
		 * Description: () operator overload for the filter base class. Allows the
     * user to access the () operator functionality of a derived class through
     * the base class.
		 * \param state is a nVect<T> object that the filter takes in to filter.
     * \return Returns a nVect<T> which represents the filtered state.
		 */
    virtual nVect<T> operator()(nVect<T>& state) = 0;
};

#endif
