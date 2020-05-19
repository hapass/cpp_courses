BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++17 -g
SOURCES = $(wildcard *.cpp)
INC=-I../../lib

main:
	mkdir -p ${BINFOLDER}
	zip -R ${BINFOLDER}/submit '*.cpp' '*.h'
	$(CXX) $(CXXFLAGS) ${INC} -o ${BINFOLDER}/main ${SOURCES}