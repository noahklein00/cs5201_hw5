// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 5 - Matrices, Filters, and Guidance
// Filename   : nTrix.hpp

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
float nTrix<T>::one_norm() const
{
	float col_sum = 0; //individual column sums
	float max_sum = 0; //maximum column sum

	for(int i = 0; i < this -> cols(); ++i)
	{
		for(int j = 0; j < this -> rows(); ++j)
		{
			col_sum += std::abs(this -> m_matrix[j][i]);
		}
		if(i == 0)
		{
			max_sum = col_sum;
		}
		else
		{
			if(col_sum > max_sum)
			{
				max_sum = col_sum;
			}
		}
		col_sum = 0;
	}
	return max_sum;
}

template <typename T>
float nTrix<T>::infinity_norm() const
{
	float row_sum = 0; //individual row sums
	float max_sum = 0; //maximum row sum

	for(int i = 0; i < this -> rows(); ++i)
	{
		for(int j = 0; j < this -> cols(); ++j)
		{
			row_sum += std::abs(this -> m_matrix[i][j]);
		}
		if(i == 0)
		{
			max_sum = row_sum;
		}
		else
		{
			if(row_sum > max_sum)
			{
				max_sum = row_sum;
			}
		}
		row_sum = 0;
	}
	return max_sum;
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
nVect<T> nTrix<T>::operator*(const nVect<T>& rhs) const
{
	if(this -> cols() != rhs.size())
	{
		throw(std::invalid_argument(std::to_string(rhs.size())));
	}

	nVect<T> ret_vect;
	ret_vect.clear();
	T temp = 0;

	for(int i = 0; i < this -> rows(); ++i)
	{
		for(int j = 0; j < this -> cols(); ++j)
		{
			temp += this -> m_matrix[i][j] * rhs[j];
		}
		ret_vect.push_back(temp);
		temp = 0;
	}
	return ret_vect;
}

template <typename T>
void nTrix<T>::clear()
{
	for(int i = 0; i < this -> rows(); i++)
	{
		delete[] m_matrix[i];
		m_matrix[i] = NULL;
	}
	delete[] m_matrix;
	m_matrix = NULL;
	m_row = 0;
	m_col = 0;
}

template <typename T>
nTrix<float> nTrix<T>::invert() const
{
	if(this -> rows() != this -> cols())
	{
		std::cout << "Cannot invert non square matrix: ";
		throw(std::range_error(std::to_string(this -> rows())));
	}
	nTrix<float> copy(*this);
	float t = 1/((this -> infinity_norm()) * (this -> one_norm()));
	nTrix<float> B = t * (this -> transpose());
	nTrix<float> identity(this -> cols(), this -> cols());

	for(int i = 0; i < identity.rows(); i++)
	{
		for(int j = 0; j < identity.cols(); j++)
		{
			if(i == j)
			{
				identity.m_matrix[i][j] = 1.0;
			}
			else
			{
				identity.m_matrix[i][j] = 0.0;
			}
		}
	}

	nTrix<float> E = identity - (B * *this);

	return r_invert(*this, B, E, identity, frobenius(B), 0);
}

template <typename T>
nTrix<T> nTrix<T>::transpose() const
{
	nTrix<T> copy(this -> cols(), this -> rows());

	for(int i = 0; i < this -> rows(); ++i)
	{
		for(int j = 0; j < this -> cols(); ++j)
		{
			copy(j,i) = this -> m_matrix[i][j];
		}
	}
	return copy;
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
std::istream& operator>>(std::istream& in, nTrix<T>& rhs)
{
	std::istream_iterator<T> in_it(in);
	std::istream_iterator<T> eos;
	nVect<T> temp;
	int rowCounter = 0;
	int colCounter = 0;
	int numCol = 0;

	temp.clear();
	while(in_it != eos)
	{
		temp.push_back(*in_it);
		colCounter++;
		if(in.peek() == 92 or in.peek() == 10)
		{
			in.ignore(2,'\n');
			if(rowCounter == 0)
			{
				numCol = colCounter;
			}
			else
			{
				if(colCounter != numCol)
				{
					std::cout << "Incorrect format for inputting a matrix: ";
					throw(std::range_error(std::to_string(colCounter)));
				}
			}
			colCounter = 0;
			rowCounter++;
		}
		++in_it;
	}

	nTrix<T> new_matrix(rowCounter, numCol);
	rhs = new_matrix;
	auto itr = temp.begin();
	for(int i = 0; i < rowCounter; i++)
	{
		for(int j = 0; j < numCol; j++)
		{
			rhs.m_matrix[i][j] = *itr;
			itr++;
		}
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

template <typename T>
nTrix<float> r_invert(const nTrix<T>& A, nTrix<float>& B,
	nTrix<float>& E, const nTrix<float>& I,  float Cerror, float Perror)
{
	B = (I + E) * B;
	Perror = Cerror;
	Cerror = frobenius(B);
	if(((std::abs(Cerror - Perror)/Perror) * 100) < .0001)
	{
		return B;
	}
	else
	{
		E = I - (B * A);
		return r_invert(A, B, E, I, Cerror, Perror);
	}
}
