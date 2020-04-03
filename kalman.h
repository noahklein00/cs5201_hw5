/*! \file
 *
 * Definitions for the kalman filter derived class. \n
 * Programmer: Noah Klein \n
 * Class: CS5201 \n
 * Assignment: Homework 5 \n
 */

#ifndef KALMAN_H
#define KALMAN_H

#include "filter.h"
#include "nTrix.h"

//! kalman class.
/*!
 * This class is a derived filter class that acts as a kalman filter to filter
 * a noisy signal from a state given a linear model.
 */
template <typename T>
class kalman: public filter<T>
{
  typedef std::initializer_list<std::initializer_list<T>> data;

  private:
    nTrix<T> m_A; /*!< A nTrix object that stores the information for the
                        * state transition matrix.
                        */
    nTrix<T> m_B; /*!< A nTrix object that stores the information for the
                   * input transition matrix.
                   */
    nVect<T> m_state; /*!< A nVect object that stores the current state of the
                       * system.
                       */
    nTrix<T> m_error; /*!< A nTrix object that stores the information for the
                       * covariance matrix for the current state.
                       */
    nTrix<T> m_process_error; /*!< A nTrix object that stores the information
                               * for the process noise of the system.
                               */
    nTrix<T> m_measurement_error; /*!< A nTrix object that stores the
                                   * information for the measurement uncertainty
                                   * matrix.
                                   */
    nTrix<T> m_identity; /*!< A nTrix object that stores information for the
                          * identity matrix.
                          */
    nTrix<T> m_K; /*!< A nTrix object that stores information for the Kalman
                   * gain.
                   */


  public:

    /*! \brief Constructor
		 *
		 * Description: Parameterized constructor for the kalman derived filter
     * class that allows the user to specify all constants and initial member
     * variables for the calculations.
		 * \param A is the constant state transition matrix.
     * \param B is the constant input transition matrix.
     * \param i_state is the initial state of the modeled system.
     * \param P is the initial state of the covariance matrix.
     * \param Q is the constant process error matrix.
     * \param R is the constant measurement uncertainty matrix.
     * \param I is the constant identity matrix in the correct dimensions of the
     * system.
		 * \post A kalman filter is initialized with all the values it needs to
     * operate.
     * \throw Throws a std::invalid_argument object if any of the defined
     * matrices would not hold up for a () operator calculation.
		 */
    kalman(const data& A, const data& B, const nVect<T>& i_state, const data& P,
       const data& Q, const data& R, const data& I);

    /*! \brief () operator
 		 *
 		 * Description: () operator overload for the kalman derived filer that steps
     * the simulation forward by one time step and calculates the neccessary
     * updates for different variables.
 		 * \param measured is the current measured state of the system.
     * \param signal is the current PID signal that was sent to the lander
     * model.
     * \return Returns a nVect<float> that represents the filtered system.
     * \pre *, +, -, and = operators must be defined for type T.
 		 * \post The filtered state is returned and the kalman filter is updated
     * by one time step.
 		 */
    nVect<float> operator()(const nVect<T>& measured, const float signal);

    /*! \brief () operator
		 *
		 * Description: () operator overload that matches the virtual function
     * defined in the filter class. This does not do anything.
		 * \param measured is the current state of the system.
     * \return Returns a nVect<float> that is the same as the input.
		 * \post Does nothing.
		 */
    virtual nVect<float> operator()(nVect<T>& measured);

};

#include "kalman.hpp"
#endif
