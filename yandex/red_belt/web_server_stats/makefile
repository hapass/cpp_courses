BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++17 -g -Wall -Werror -O3
SOURCES = $(wildcard *.cpp)
INC=-I../../lib

main:
	mkdir -p ${BINFOLDER}
	zip -R ${BINFOLDER}/submit 'stats.cpp' 'stats.h'
	$(CXX) $(CXXFLAGS) ${INC} -o ${BINFOLDER}/main ${SOURCES}