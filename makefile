.PHONY:| all generate program

all: generate program

generate: generator.cpp
	g++ -pg generator.cpp -o generate
	./generate

program:matrix.cpp Matrix.hpp Interface.hpp #add_mult.hpp
	g++ -pg matrix.cpp -I./ -o program -ftime-report
	./program
#test: test.cpp
#	g++ -pg test.cpp -o test -ftime-report
#	./test	
clean:
	rm -f generate program 
