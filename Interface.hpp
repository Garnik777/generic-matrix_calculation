#ifndef _INTERFACE_HPP__
#define _INTERFACE_HPP__
#include "Matrix.hpp"
#include <iostream>
#include <cstddef>

template <typename T> struct interface {};

template <typename T>
struct interface<Matrix<T> > {
	typedef typename Matrix<T>::element_type element_type;
	
	static T get_element(const Matrix<T>& a, std::size_t i, std::size_t j) {
		 return a(i, j);
	} 

	static void set_element(Matrix<T>& a, std::size_t i, std::size_t j, T x) {
		 a(i, j) = x; 
	}

	static std::size_t  getMatrixRow(const Matrix<T>& a ){
		return a.getMatrixRow();
	}
	
	static std::size_t getMatrixCol(const Matrix<T>& a) {
		return a.getMatrixCol();
	}	

};
#endif
