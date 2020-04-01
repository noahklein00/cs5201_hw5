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

class lander
{
  private:
    float m_step;
    float m_signal;
    float radius = 4;
    float moment = 100000;
    nVect<float>* m_state;
    nVect<float>* m_new_state;
    PID* controller;

  public:

    // Essential //
    lander();
    lander(const float step_size,
      const std::initializer_list<float>& i_state, const float set_point);
    ~lander();

    // Accessors //
    // Mutators //

    nVect<float> operator()(const nVect<float>& input);

    // Friends //

		friend std::ostream& operator<<(std::ostream& out, const lander& rhs);

};

// Extras //

std::ostream& operator<<(std::ostream& out, const lander& rhs);

#include "lander.hpp"
#endif
