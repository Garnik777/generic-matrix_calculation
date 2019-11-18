#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <string>

int z = 1;
using element_type = double;
void Input_File_Parameters(unsigned int& rows_out, unsigned int& columns_out,
			   unsigned int& number_out, std::string& file_name_out)
{
       	std::cout << "For generation of matrix file you should\n";	
	std::cout << "enter file names: ";
	std::cin >> file_name_out;
	std::cout << "enter number of rows: ";
	std::cin >> rows_out;
	std::cout << "enter number of columns: ";
	std::cin >> columns_out;
	std::cout << "enter number of matrices: ";
	std::cin >> number_out;
}

void Matrix_File_Generation(unsigned int rows, unsigned int columns,
				unsigned int number, std::string file_name)
{
	std::ofstream fout(file_name, std::ios::out);
	if(!fout.is_open())
	{
		std::cout << "ERROR: file not created\n";
		exit(1);
	}
		
	fout << rows << " x " << columns << std::endl;
	fout <<"\n";
	
	srand(time(0));
	int count = number;
	while (number)
	{
		fout << "<" << (count - number + 1) << ">\n"; //addition 

		element_type n;
		for(int i = 0; i < rows; ++i)
        	{
                	for(int j = 0; j < columns; ++j)
                	{
                        	n = rand() % 198 - 99;
				if(!(fout << std::setw(3) << n << ' '))
				{
					std::cout << "ERROR: file not created\n";
					exit(1);
		       		}
               		}

			fout << '\n';
	       	}

		fout << '\n';
		--number;
	}
	std::cout << file_name << " file successfully created!\n";
}


int main()
{
	int step;
	do{
		unsigned int rows, columns, number;
	std::string file_name;

		Input_File_Parameters(rows, columns, number, file_name);

		Matrix_File_Generation(rows, columns, number, file_name);
		
		std::cout << "To create the next file, enter \" 1 \" or any key to stop the generation process: ";
		std::cin >> step;

	} while(step == 1);

	return 0;
}
	
