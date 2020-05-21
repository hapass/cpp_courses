BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++17 -g
SOURCES_ONE = sort_2_way.cpp
SOURCES_TWO = sort_3_way.cpp
INC=-I../../lib

main:
	mkdir -p ${BINFOLDER}
	$(CXX) $(CXXFLAGS) ${INC} -o ${BINFOLDER}/main_1 ${SOURCES_ONE}
	$(CXX) $(CXXFLAGS) ${INC} -o ${BINFOLDER}/main_2 ${SOURCES_TWO}