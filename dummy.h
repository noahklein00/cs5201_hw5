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

template <typename T>
class dummy: public filter<T>
{
  public:

    /*! \brief
		 *
		 * Description:
		 * \param
     * \return
     * \pre
		 * \post
		 * \throw
		 */
    virtual nVect<T> operator()(nVect<T>& state);
};

#include "dummy.hpp"
#endif
