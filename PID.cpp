// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 5 - Matrices, Filters, and Guidance
// Filename   : PID.cpp

#include "nVect.h"
#include "PID.h"

PID::PID(const float step, const float d_value)
{
	if(step <= 0) throw(std::domain_error(std::to_string(step)));

	m_step = step;
	desired_value = d_value;
	m_Cerror = 0;
	m_Perror = 0;
	m_signal = 0;
	m_kstore = nVect<float>(3);
	m_kstore[0] = 1000; //P
	m_kstore[1] = 1000; //I
	m_kstore[2] = 2000; //D
}

PID::PID(const PID& rhs)
{
	m_step = rhs.m_step;
	desired_value = rhs.desired_value;
	m_Cerror = rhs.m_Cerror;
	m_Perror = rhs.m_Perror;
	m_signal = rhs.m_signal;
	m_kstore = rhs.m_kstore;
}

PID& PID::operator=(const PID& rhs)
{
	m_step = rhs.m_step;
	desired_value = rhs.desired_value;
	m_Cerror = rhs.m_Cerror;
	m_Perror = rhs.m_Perror;
	m_signal = rhs.m_signal;
	m_kstore = rhs.m_kstore;
	return *this;
}


float PID::operator()(const float curr_value)
{
	m_Perror = m_Cerror;
	m_Cerror = ((curr_value - desired_value)/desired_value * 100);

	//std::cout << "error: " << m_Cerror << std::endl;

	past += (m_Perror + (m_Cerror - m_Perror)/2) * m_step;
	future = (m_Cerror - m_Perror)/m_step;
	m_signal = (m_kstore[0] * m_Cerror) + (m_kstore[1] * past) +
		(m_kstore[2] * future);

	return m_signal;
}

float& PID::operator[](const int access)
{
	return m_kstore[access];
}

void PID::reset(const float new_d)
{
	desired_value = new_d;
	return;
}

void PID::set_step(const float new_step)
{
	m_step = new_step;
	return;
}
