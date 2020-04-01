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

template <typename T>
class filter
{
  public:
    virtual nVect<T>& operator()(nVect<T>& state) = 0;
};

#endif
