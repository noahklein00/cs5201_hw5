// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 5 - Matrices, Filters, and Guidance
// Filename   : nTrix.hpp

template <typename T>
nVect<T> dummy<T>::operator()(nVect<T>& state)
{
  //std::cout << "dummy operator()" << std::endl;
  return state;
}
