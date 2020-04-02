// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 5 - Matrices, Filters, and Guidance
// Filename   : lander.hpp

//***************************** Essentials **********************************//

lander::lander()
{
  m_step = .1;
  m_signal = 0;
  m_state = new nVect<float>(3);
  m_controller = new PID(.1,0);
}

lander::lander(const float step_size,
  const std::initializer_list<float>& i_state, const float set_point)
{
  if(step_size <= 0)
  {
    throw(std::domain_error(std::to_string(step_size)));
  }

  m_step = step_size;
  m_signal = 0;
  m_state = new nVect<float>(i_state);
  m_controller = new PID(step_size, set_point);
}

lander::~lander()
{
  delete m_state;
  delete m_controller;
}

//***************************** Accessors ***********************************//

const float lander::getSignal() const
{
  return m_signal;
}

//***************************** Mutators ************************************//

nVect<float> lander::operator()(const nVect<float>& input)
{
  *m_state = input;

  //PID controller outputs a signal
  m_signal = (*m_controller)((*m_state)[0]);

  //signal is used by the model to calculate the next step
  (*m_state)[2] = (m_radius * -m_signal)/m_moment;
  (*m_state)[1] += ((*m_state)[2]) * m_step;
  (*m_state)[0] += .5 * ((*m_state)[1]) * m_step;

  return *m_state;
}

//***************************** Friends *************************************//

std::ostream& operator<<(std::ostream& out, const lander& rhs)
{
  out << "Alpha: " << (*rhs.m_state)[2] << ", Omega: " << (*rhs.m_state)[1] <<
    ", Theta: " << (*rhs.m_state)[0];
  return out;
}

//***************************** Extras **************************************//
