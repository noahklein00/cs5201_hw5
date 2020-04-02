/*! \file
 *
 * Definitions for the dummy filter derived class. \n
 * Programmer: Noah Klein \n
 * Class: CS5201 \n
 * Assignment: Homework 5 \n
 */

#ifndef DUMMY_H
#define DUMMY_H

#include "filter.h"

//! dummy class.
/*!
 * This class is a derived filter class that acts as a passthrough of a state
 * without actually filtering it.
 */
template <typename T>
class dummy: public filter<T>
{
  public:

    /*! \brief () operator
		 *
		 * Description: () operator overload that inherits from the base class
     * to allow the user to pass a nVect<T> state through.
		 * \param state is the state that the user wants to pass through
     * unfiltered.
     * \return Returns a new nVect<T> that has the same values as the
     * parameter.
		 */
    virtual nVect<T> operator()(nVect<T>& state);
};

#include "dummy.hpp"
#endif
