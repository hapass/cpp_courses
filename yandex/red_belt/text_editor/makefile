BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++17 -g -Wall -Werror -O3
SOURCES = $(wildcard *.cpp)
INC=-I../../lib

main:
	mkdir -p ${BINFOLDER}
	$(CXX) $(CXXFLAGS) ${INC} -o ${BINFOLDER}/main ${SOURCES}