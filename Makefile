# CXX Make variable for compiler
CXX=g++
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -g

PXXFLAG = -pthread
# output: main.o dictionary.o
# 	g++ main.o dictionary.o -o countwords

# main.o:	main.cpp
# 	g++ -c main.cpp

# dictionary.o: dictionary.cpp dictionary.h
# 	g++ -c dictionary.cpp

# Rules format:
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
countwords :dictionary.o populatetree.o countwords.o main.o 
	$(CXX) $(CXXFLAGS) $(PXXFLAG) -o dicttest $^

main.o: main.cpp

dictionary.o : dictionary.cpp 

populatetree.o : populatetree.cpp 

countwords.o : countwords.cpp

clean :
	rm *.o
