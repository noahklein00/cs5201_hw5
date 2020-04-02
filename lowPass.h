/*! \file
 *
 * Definitions for the lowpass filter derived class. \n
 * Programmer: Noah Klein \n
 * Class: CS5201 \n
 * Assignment: Homework 5 \n
 */

#ifndef LOWPASS_H
#define LOWPASS_H

#include "filter.h"

//! lowPass class.
/*!
 * This class acts as a lowPass filter derived from the filter base class.
 */
template <typename T>
class lowPass: public filter<T>
{
  private:
    float m_alpha; /*!< A float that stores the more accurate calculation
                    * of alpha used in the lowpass filter calculation.
                    */
    nVect<T> m_prev_state; /*!< The previous state of the system to be used
                            * in the lowpass filter calculation.
                            */

  public:

    /*! \brief Constructor
		 *
		 * Description: Parameterized constructor for the lowPass derived filter
     * class. This constructor uses the stepSize and f parameters to perform
     * the more accurate calculation of alpha for the lowPass filter method.
		 * \param stepSize is the change in time for each increment of the lowPass
     * filter iteration.
     * \param f is the frequency for each increment of the lowPass filter
     * iteration.
     * \param i_state is the initial state of the system. This assumes that
     * the state can always be represented as a vector.
		 * \post Initializes a lowPass filter with an alpha value and initial state
     * that filters a noisy signal for a given state.
		 */
    lowPass(const float stepSize, const float f, const nVect<T> i_state);

    /*! \brief () operator
		 *
		 * Description: () operator overload for the lowPass derived filter that
     * takes a new state and weights that against the previous states to create
     * a weighted average of the weighted average.
		 * \param state is the current state of the system to be weighted against
     * the current stored state m_prev_state.
     * \return Returns the new weighted current state.
     * \pre * and + operators must be defined for type T.
		 * \post The previous state is updated with the proper weights of the
     * previous and current states.
		 */
    virtual nVect<T> operator()(nVect<T>& state);
};

#include "lowPass.hpp"
#endif
