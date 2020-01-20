.PHONY:| all generate program

all: generate program

generate: generator.cpp
	g++ -pg --coverage generator.cpp -o generate
	./generate
	@gcov generate.cpp -m
	
program:matrix.cpp Matrix.hpp Interface.hpp #add_mult.hpp
	g++ -pg --coverage matrix.cpp -I./ -o program -ftime-report
	./program
	@gcov matrix.cpp -m
clean:
	rm -f generate program 
