// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 5 - Matrices, Filters, and Guidance
// Filename   : kalman.hpp

template <typename T>
kalman<T>::kalman(const data& A, const data& B, const nVect<T>& i_state,
  const data& P, const data& Q, const data& R, const data& I)
{
  m_A = A;
  m_B = B;
  m_state = i_state;
  m_error = P;
  m_process_error = Q;
  m_measurement_error = R;
  m_identity = I;
  m_K = nTrix<T>(m_A.rows(),m_A.cols());

  if(m_A.cols() != m_state.size())
  {
    std::cout << "invalid size for A matrix leads to ";
    throw(std::invalid_argument(std::to_string(m_A.cols())));
  }
  if(m_B.cols() != m_state.size())
  {
    std::cout << "invalid size for B matrix leads to ";
    throw(std::invalid_argument(std::to_string(m_B.cols())));
  }
  if(m_A.cols() != m_error.cols())
  {
    std::cout << "invalid size for P matrix leads to ";
    throw(std::invalid_argument(std::to_string(m_error.cols())));
  }
  if(m_process_error.rows() != m_error.rows() ||
    m_process_error.cols() != m_error.cols())
  {
    std::cout << "invalid size for Q matrix leads to ";
    throw(std::invalid_argument(std::to_string(m_process_error.cols())));
  }
  if(m_error.rows() != m_measurement_error.rows() ||
    m_error.cols() != m_measurement_error.cols())
  {
    std::cout << "invalid size for R matrix leads to ";
    throw(std::invalid_argument(std::to_string(m_measurement_error.cols())));
  }
  if(m_error.rows() != m_identity.rows() || m_error.cols() != m_identity.cols())
  {
    std::cout << "invalid size for I matrix leads to ";
    throw(std::invalid_argument(std::to_string(m_identity.cols())));
  }
}

template <typename T>
nVect<float> kalman<T>::operator()(const nVect<T>& measured,
   const float signal)
{
  nVect<T> control({0,0,signal});
  nVect<T> copy(measured);

  m_state = (m_A * m_state) + (m_B * control);
  m_error = m_A * m_error * (m_A.transpose()) + m_process_error;
  m_K = m_error * (m_error + m_measurement_error).invert();
  m_state = m_state + m_K * (copy - m_state);
  m_error = (m_identity - m_K) * m_error;;
  return m_state;
}

template <typename T>
nVect<float> kalman<T>::operator()(nVect<T>& measured)
{
  return measured;
}
