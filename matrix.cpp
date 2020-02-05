#include "Interface.hpp"
#include "Matrix.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <iomanip>

using element_type = double;
template <typename T>
struct Readfile{
private:	
	const char* filename;
	std::size_t row;
        std::size_t col;
public:
	std::ifstream file_stream;	
	Readfile(const char* fn): filename(fn) {
		file_stream.open(filename, std::ios::in);
		assert(file_stream.is_open() && "file is not opening\n");
		char delimiter;
		std::string text;
		if(!(file_stream >> row >> delimiter >> col >> text)) {
			std::cout << "can not read first row value\n";
		}	
	}


	bool read(T & i) {
 		if(file_stream >> i) {
			return true;
		}else{
			return false;
		}	
	}
		
	bool read(char& c) {
		if(file_stream >> c) {
			return true;
		}else{
			return false;
		}
	}

	std::size_t read_row_size() {
		return int(row);
	}

	std::size_t read_col_size() {
		return int(col);
	}	
	
	~Readfile() {
		file_stream.close();	
	}
};	

template <typename T>
struct Writefile{
private:	
	const char* filename;
	std::size_t row;
        std::size_t col;
	std::size_t stream_width;

public:
	std::ofstream fout_stream;	
	Writefile(const char* fn, std::size_t sw,std::size_t r,std::size_t c)
	       	: filename(fn), stream_width(sw), row(r), col(c){
		fout_stream.open(filename, std::ios::out);
		assert(fout_stream.is_open() && "file_stream is not open\n");
		if(!(fout_stream << row << " x " << col << "\n")) {
			std::cout << " can not write first row value\n";
		}
	}

	bool write(T i) {
		if(fout_stream << std::setw(stream_width)<< i) {
			return true;
		}else{
			return false;
		}	
	}

	bool char_writer(char c) {
		if(fout_stream << c) {
			return true;
		}else{
			return false;
		}	
	}

	~Writefile() {
		fout_stream.close();
	}	
};

template <typename T>
void readMatrix(Readfile<T>& r,Matrix<T>& m) {
	
	using MI = interface<Matrix<T>>;
	char c;
	typename MI::element_type x = 0;
	r.read(c);
	r.read(x);
	r.read(c);
	for(std::size_t i = 0;i < MI::getMatrixRow(m);i++)
	{
		for(std::size_t j = 0;j< MI::getMatrixCol(m);j++)
		{
			MI::set_element(m,i, j, x);
			if(r.read(x))
			{
				std::cout<< MI::get_element(m,i,j) <<" ";
			}	
			else{
				std::cout<<"can not read"<<std::endl;
			}
		}
		
			std::cout<< std::endl;
	} 
			std::cout<<"read matrix done"<<std::endl;
}


template<typename T>
void AddMatrix(const Matrix<T>& a, const Matrix<T>& b,Matrix<T>& t1)
{
	using MI = interface<Matrix<T>>;
	assert(MI::getMatrixRow(a) == MI::getMatrixRow(b));
	assert(MI::getMatrixCol(a) == MI::getMatrixCol(b));
	for(std::size_t i = 0;i < MI::getMatrixRow(a);i++)
	{
			 typename MI::element_type result = 0;

		  for(std::size_t j=0;j < MI::getMatrixCol(b);j++)
		  {
			 //typename MI::element_type result = 0;
			result = MI::get_element(a, i, j) + MI::get_element(b,i,j);
			 MI::set_element(t1, i,j,result);
		  }
	}
	std::cout << "add matrix done" <<std::endl;
}

template <typename T>
void MultMatrix(const Matrix<T>& a, const Matrix<T>& b, Matrix<T>& y)
{
	using MI = interface<Matrix<T>>;
	assert(MI::getMatrixCol(a) == MI::getMatrixRow(b));
	assert(MI::getMatrixRow(a) == MI::getMatrixRow(y));
	assert(MI::getMatrixCol(b) == MI::getMatrixCol(y));
	typename MI::element_type transpos = (MI::getMatrixRow(a) >= 100 && MI::getMatrixCol(b) >= 100) ?  1 : 0;
	for(std::size_t i = 0;i < MI::getMatrixRow(a);i++)
	{
		for(std::size_t j = 0; j< MI::getMatrixCol(b);j++)
		{
			typename MI::element_type sum = 0;
			for(std::size_t k = 0; k < MI::getMatrixCol(a);k++)
			{	
				typename MI::element_type temp = 0;
				//transposing the matrix
					if(transpos) {
						sum+= MI::get_element(a, i,k) * MI::get_element(b, k ,j);
						MI::set_element(y,i,j,sum);
						temp = MI::get_element(y, j,i);
						MI::set_element(y, i, j,temp);
						std::cout << "mtnuma traspos"<< std::endl;
					}else{	
						sum+= MI::get_element(a,i,k) * MI::get_element(b, k, j);
					}	
			}
			MI::set_element(y, i,j, sum);
				std::cout << MI::get_element(y,i,j) <<' ';
		}
		std::cout << std::endl;	
	}
		std::cout <<"mult matrix done"<<std::endl;
}

template <typename T>
void WriteMatrix(const Matrix<T>& y,Writefile<T>& wy)
{
	using MI = interface<Matrix<T>>;

	typename MI::element_type x = 0;
	for(std::size_t i = 0;i <MI::getMatrixRow(y);i++)
	{
		for(std::size_t j = 0;j < MI::getMatrixCol(y); j++)
		{
			x = MI::get_element(y, i, j);
			if(wy.write(x))
			{
				wy.fout_stream << ' ';
			}else{
				std::cout <<"can not write file"<<std::endl;
			 }
		}
			wy.fout_stream << '\n';
	}
		std::cout<<"write matrix done"<<std::endl;
}

int main()
{
		
	std::size_t stream_width = 12;
	Readfile<float> ra("a.txt"),rb("b.txt"),rc("c.txt"),rd("d.txt");
	Writefile<float> wy("y.txt", stream_width, ra.read_row_size(), rd.read_col_size());
	Matrix<float> A(ra.read_row_size(), ra.read_col_size()),
			    B(rb.read_row_size(), ra.read_col_size()),
			    T1(ra.read_row_size(),ra.read_col_size()),
			    C(rc.read_row_size(), rc.read_col_size()),
			    D(rd.read_row_size(), rd.read_col_size()),
			    T2(rc.read_row_size(),rc.read_col_size()),
			    Y(ra.read_row_size(), rd.read_col_size());
	readMatrix(ra, A);
	readMatrix(rb, B);
	AddMatrix(A,B,T1);
	readMatrix(rc, C);
	readMatrix(rd, D);
	AddMatrix(C,D,T2);
	MultMatrix(T1,T2,Y);
	WriteMatrix(Y,wy); 
    
return 0;
}


