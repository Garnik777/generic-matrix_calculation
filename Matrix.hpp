#ifndef _MATRIX_HPP__
#define _MATRIX_HPP__
#include <cstddef>

template <typename T>
struct Matrix{
public:	
	typedef T element_type;
	Matrix(std::size_t M, std::size_t N): m_row(M), m_column(N) {
		m_data = new T [M * N];
	}
	
	std::size_t getMatrixRow() const {
		return m_row;
	}

	std::size_t getMatrixCol() const {
		return m_column;
	}

	const element_type& operator ()(std::size_t i, std::size_t j) const {
		return m_data[i * getMatrixCol() + j];
	}

	element_type& operator() (std::size_t i, std::size_t j) {
		return m_data[i * getMatrixCol() +j];
	}
	
	~Matrix() {
		delete[] m_data;
	}	
private:	
	std::size_t m_row;
	std::size_t m_column;
	T* m_data;

};

/*template <>
struct Matrix{
public:	
	typedef double element_type;
	Matrix(std::size_t M, std::size_t N): m_row(M), m_column(N) {
		m_data = new element_type [M * N];
	}

	std::size_t getMatrixRow() const {
		return m_row;
	}

	std::size_t getMatrixCol()const {
		return m_column;
	}
	
	element_type& operator()(std::size_t i, std::size_t j) {
		return m_data[M][N];
	}

	const	element_type& operator()(std::size_t i, std::size_t j) {
		return m_data[M][N];
	}
private:
	std::size_t m_row;
	std::size_t m_row;
	element_type* m_data;
}	
*/

#endif
