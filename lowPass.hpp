// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 5 - Matrices, Filters, and Guidance
// Filename   : nTrix.hpp

template <typename T>
lowPass<T>::lowPass(const float stepSize, const float f, const nVect<T> i_state)
{
  m_alpha = 1.0 - std::exp(-f * stepSize);
  m_prev_state = i_state;
}

template <typename T>
nVect<T> lowPass<T>::operator()(nVect<T>& state)
{
  m_prev_state = (m_alpha * m_prev_state) + ((float)(1.0-m_alpha) * state);

  return m_prev_state;
}
