/*! \file
 *
 * Definitions for the lander class. \n
 * Programmer: Noah Klein \n
 * Class: CS5201 \n
 * Assignment: Homework 5 \n
 */

#ifndef LANDER_H
#define LANDER_H

#include "nVect.h"
#include "PID.h"
#include "filter.h"

//! lander class.
/*!
 * This class acts acts as a model for the lander simulation that steps with a
 * discrete time step to simulate a lander using a PID controller to correct
 * a signal received about the landers angle measurements.
 */
class lander
{
  private:
    float m_step; /*!< A float that stores the step size for the system. */
    float m_signal; /*!< A float that stores the control signal from the stored
                     * PID controller.
                     */
    float m_radius = 4.0; /*!< A float that stores the radius variable
                           * used in the calculaion of the angular acceleration.
                           */
    float m_moment = 100000.0; /*!< A float that stores the moment variable used
                                * in the calculation of the angular
                                * acceleration.
                                */
    nVect<float>* m_state; /*!< A nVect<float>* that stores the current state of
                            * the system.
                            */
    PID* m_controller; /*!< A PID* that stores a PID controller for a system. */

  public:

    // Essential //

    /*! \brief Constuctor
		 *
		 * Description: Default constructor for the lander class that initializes
     * the float variables with a default value but doesn't provide either a
     * m_state or m_controller variable.
		 * \post A lander class is initialized with default values for all its
     * member variables.
		 */
    lander();

    /*! \brief Constructor
		 *
		 * Description: Parameterized constructor for the lander class that takes
     * a user defined step size, initial state, and PID controller to set up
     * the lander class.
		 * \param step_size is the time step for the lander class model.
     * \param i_state is the initial state of the system represented as a
     * nVect<float> object.
     * \param set_point is the target set point for the theta member of the
     * state.
		 * \post A lander object is initialized with the proper values to perform
     * discrete time steps on it.
		 * \throw Throws a std::domain_error object if the step size is <= 0.
		 */
    lander(const float step_size,
      const std::initializer_list<float>& i_state, const float set_point);

    /*! \brief Destructor
		 *
		 * Description: Desctructor for the lander class that safely deallocates the
     * memory of the lander object.
		 * \post The lander objects reserved memory is safely deallocated.
		 */
    ~lander();

    // Accessors //

    /*! \brief Signal accessor
		 *
		 * Description: Accessor for the m_signal member variable to be output to
     * the user.
     * \return Returns a const float that represents the signal returned to
     * the system from the PID controller.
		 */
    const float getSignal() const;

    // Mutators //

    /*! \brief () operator
		 *
		 * Description: () operator overload for the lander class that steps the
     * model forward one time step.
		 * \param input is the current state of the system. This allows the user
     * to add noise and/or filter the system in between time steps.
     * \return Returns a nVect<float> to represent the updated system.
		 * \post The model is stepped forward by one time step and the proper member
     * variables are updated with the current values.
		 */
    nVect<float> operator()(const nVect<float>& input);

    // Friends //

    /*! \brief << operator
		 *
		 * Description: << operator overload for the lander class that allows the
     * user to print the state information in a readable way.
		 * \param out is the ostream object passed to the function.
     * \param rhs is the lander object to be output to the user.
     * \return Returns the ostream object.
		 * \post The lander object is output to the user.
		 */
		friend std::ostream& operator<<(std::ostream& out, const lander& rhs);

};

// Extras //

/*! \brief << operator
 *
 * Description: << operator overload for the lander class that allows the
 * user to print the state information in a readable way.
 * \param out is the ostream object passed to the function.
 * \param rhs is the lander object to be output to the user.
 * \return Returns the ostream object.
 * \post The lander object is output to the user.
 */
std::ostream& operator<<(std::ostream& out, const lander& rhs);

#include "lander.hpp"
#endif
