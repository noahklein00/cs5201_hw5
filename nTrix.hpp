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

	unsigned short row_counter = 0;
	unsigned short col_counter = 0;

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
unsigned short nTrix<T>::rows() const
{
	return m_row;
}

template <typename T>
unsigned short nTrix<T>::cols() const
{
	return m_col;
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

	short sum = 0;
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
