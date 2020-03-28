// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 4 - Implicit Solvers, p-norms, and
//					Insulin/Glucose Dynamics
// Filename   : nVect.hpp

//***************************** Essentials **********************************//

template <typename T>
nTrix<T>::nTrix()
{
	//default 2x2 matrix
	m_row = 2;
	m_col = 2;
	m_matrix = new T*[m_row];

	for(int i = 0; i < m_row; i++)
	{
		m_matrix[i] = new T[m_col];
	}
}

template <typename T>
nTrix<T>::nTrix(const std::initializer_list<std::initializer_list<T>> grid)
{
	m_row = grid.size();
	m_col = grid.begin() -> size();
	m_matrix = new T*[m_row];

	short row_counter = 0;
	short col_counter = 0;

	for(auto r_itr = grid.begin(); r_itr != grid.end(); r_itr++)
	{
		if(r_itr -> size() != m_col)
		{
			throw(std::domain_error(std::to_string(r_itr -> size())));
		}

		m_matrix[row_counter] = new T[m_col];

		for(auto c_itr = r_itr -> begin(); c_itr != r_itr -> end(); c_itr++)
		{
			m_matrix[row_counter][col_counter] = *c_itr;
			col_counter++;
		}
		col_counter = 0;
		row_counter++;
	}
}

template <typename T>
nTrix<T>::nTrix(const short num_rows, const short num_cols)
{
	if(num_rows < 0)
	{
		throw(std::domain_error(std::to_string(num_rows)));
	}
	if(num_cols < 0)
	{
		throw(std::domain_error(std::to_string(num_cols)));
	}

	m_row = num_rows;
	m_col = num_cols;
	m_matrix = new T*[m_row];

	for(int i = 0; i < m_row; i++)
	{
		m_matrix[i] = new T[m_col];
	}
}

template <typename T>
nTrix<T>::nTrix(const nVect<T>& rhs)
{
	m_row = rhs.size();
	m_col = 1;
	m_matrix = new T*[m_row];

	for(int i = 0; i < m_row; i++)
	{
		m_matrix[i] = new T[m_col];
		m_matrix[i][0] = rhs[i];
	}
}

template <typename T>
nTrix<T>::nTrix(const nTrix<T>& rhs)
{
	m_row = rhs.m_row;
	m_col = rhs.m_col;
	m_matrix = new T*[m_row];

	for(int i = 0; i < m_row; i++)
	{
		m_matrix[i] = new T[m_col];
		for(int j = 0; j < m_col; j++)
		{
			m_matrix[i][j] = rhs.m_matrix[i][j];
		}
	}
}

template <typename T>
nTrix<T>& nTrix<T>::operator=(const nTrix<T>& rhs)
{
	for(int i = 0; i < m_row; i++)
	{
		delete[] m_matrix[i];
		m_matrix[i] = NULL;
	}
	delete[] m_matrix;
	m_matrix = NULL;

	m_row = rhs.m_row;
	m_col = rhs.m_col;
	m_matrix = new T*[m_row];

	for(int i = 0; i < m_row; i++)
	{
		m_matrix[i] = new T[m_col];
		for(int j = 0; j < m_col; j++)
		{
			m_matrix[i][j] = rhs.m_matrix[i][j];
		}
	}

	return *this;
}

template <typename T>
nTrix<T>::~nTrix()
{
	for(int i = 0; i < m_row; i++)
	{
		delete[] m_matrix[i];
		m_matrix[i] = NULL;
	}
	delete[] m_matrix;
	m_matrix = NULL;
}

//***************************** Accessors ***********************************//

template <typename T>
short nTrix<T>::rows() const
{
	return m_row;
}

template <typename T>
short nTrix<T>::cols() const
{
	return m_col;
}

template <typename T>
const T& nTrix<T>::operator()(const int row_index, const int col_index) const
{
	if(row_index < 0 || row_index >= m_row)
	{
		throw(std::domain_error(std::to_string(row_index)));
	}
	if(col_index < 0 || col_index >= m_col)
	{
		throw(std::domain_error(std::to_string(col_index)));
	}

	return m_matrix[row_index][col_index];
}

template <typename T>
float frobenius(const nTrix<T>& rhs)
{
	float norm = 0;
	for(int i = 0; i < rhs.rows(); i++)
	{
		for(int j = 0; j < rhs.cols(); j++)
		{
			norm += (rhs(i,j) * rhs(i,j));
		}
	}
	return sqrt(norm);
}

//***************************** Mutators ************************************//

template <typename T>
T& nTrix<T>::operator()(const int row_index, const int col_index)
{
	if(row_index < 0 || row_index >= m_row)
	{
		throw(std::domain_error(std::to_string(row_index)));
	}
	if(col_index < 0 || col_index >= m_col)
	{
		throw(std::domain_error(std::to_string(col_index)));
	}

	return m_matrix[row_index][col_index];
}

template <typename T>
nTrix<T> nTrix<T>::operator+(const nTrix<T>& rhs) const
{
	if(this -> rows() != rhs.rows())
	{
		throw(std::invalid_argument(std::to_string(this -> rows())));
	}
	if(this -> cols() != rhs.cols())
	{
		throw(std::invalid_argument(std::to_string(this -> cols())));
	}

	nTrix<T> copy(*this);

	for(int i = 0; i < copy.m_row; i++)
	{
		for(int j = 0; j < copy.m_col; j++)
		{
			copy.m_matrix[i][j] += rhs.m_matrix[i][j];
		}
	}

	return copy;
}

template <typename T>
nTrix<T> nTrix<T>::operator-(const nTrix<T>& rhs) const
{
	return *this + (-rhs);
}

template <typename T>
nTrix<T> nTrix<T>::operator-() const
{
	return (*this*(-1));
}

template <typename T>
nTrix<T> nTrix<T>::operator*(const nTrix<T>& rhs) const
{
	if(this -> cols() != rhs.rows())
	{
		throw(std::invalid_argument(std::to_string(this -> cols())));
	}

	double sum = 0;
	short left_row = 0;
	short right_col = 0;

	nTrix<T> copy(this -> rows(),rhs.cols());

	for(int i = 0; i < copy.rows(); i++)
	{
		for(int j = 0; j < copy.cols(); j++)
		{
			for(int k = 0; k < this -> cols(); k++)
			{
				sum += (this -> m_matrix[left_row][k] * rhs.m_matrix[k][right_col]);
			}
			copy(i,j) = sum;
			sum = 0;
			right_col++;
		}
		right_col = 0;
		left_row++;
	}

	return copy;
}

template <typename T>
nTrix<T> nTrix<T>::operator*(const nVect<T>& rhs) const
{
	nTrix<T> copy(rhs);
	return *this * copy;
}

template <typename T>
nTrix<float> invert(const nTrix<T>& A)
{
	if(A.rows() != A.cols())
	{
		throw(std::invalid_argument(std::to_string(A.rows())));
	}

	const int N = A.rows();
	nTrix<float> P(N,N);
	nTrix<float> copy(A);

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(i == j)
			{
				P(i,j) = 1.0;
			}
			else
			{
				P(i,j) = 0.0;
			}
		}
	}

	return r_invert(frobenius(P),P,copy);
}

nTrix<float> r_invert(const double I, nTrix<float> P, const nTrix<float> A)
{
	double temp; //stores the frobenius norm of the predictor

	P = (P * 2) - (A * P * P);
	temp = frobenius(P);

	if(((std::abs(temp - I) / I) * 100) < .000001)
	{
		return P;
	}
	else
	{
		return r_invert(temp, P, A);
	}
}

template <typename T>
void nTrix<T>::clear(nTrix<T>& rhs)
{
	for(int i = 0; i < rhs.rows(); i++)
	{
		delete[] rhs.m_matrix[i];
		rhs.m_matrix[i] = NULL;
	}
	delete[] rhs.m_matrix;
	rhs.m_matrix = NULL;
	rhs.m_row = 0;
	rhs.m_col = 0;
}

//***************************** Friends *************************************//

template <typename T>
std::ostream& operator<<(std::ostream& out, const nTrix<T>& rhs)
{
	for(int i = 0; i < rhs.m_row; i++)
	{
		for(int j = 0; j < rhs.m_col; j++)
		{
			out << rhs.m_matrix[i][j] << " ";
		}
		if(i < rhs.m_row -1)
		{
			out << std::endl;
		}
	}
	return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, const nTrix<T>& rhs)
{
	// int num_row = -1;
	// int counter = 0;
	// std::string line;
	// nVect<T> temp;
	//
	// while(in)
	// {
	// 	std::getline(in, line);
	//
	// 	for(auto itr = line.cbegin(); itr != line.cend(); ++itr)
	// 	{
	// 		if(!isspace(*itr))
	// 		{
	// 			std::cout << *itr;
	// 			temp.push_back(static_cast<T>(*itr));
	// 		}
	// 		std::cout << std::endl;
	// 	}
	// 	num_row++;
	// 	counter = 0;
	// }
	// std::cout << temp << std::endl;
	//
	// std::cout << temp << std::endl;
	// std::cout << num_row << std::endl;
	// std::cout << "here" << std::endl;
	//
	// return in;
	nVect<T> temp;
	std::string line;
	char c;
	int lineCounter = 0;

	std::istream_iterator<T> in_it(in);
	std::istream_iterator<T> eos;

	temp.clear();

	for(;in_it != eos; ++in_it)
	{
		in.get(c);
		if(c == '\n')
		{
			lineCounter++;
		}
		temp.push_back(*in_it);
	}


	return in;
}

//***************************** Extras **************************************//

template <typename T>
nTrix<T> operator*(const nTrix<T>& lhs, const float scalar)
{
	nTrix<T> copy(lhs);
	for(int i = 0; i < copy.rows(); i++)
	{
		for(int j = 0; j < copy.cols(); j++)
		{
			copy(i,j) *= scalar;
		}
	}
	return copy;
}

template <typename T>
nTrix<T> operator*(const float scalar, const nTrix<T>& rhs)
{
	return (rhs*scalar);
}

template <typename T>
nTrix<T> operator*(const nVect<T>& lhs, const nTrix<T>& rhs)
{
	nTrix<T> copy(lhs);
	return copy * rhs;
}















