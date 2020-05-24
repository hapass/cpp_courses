BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++17 -g
SOURCES_PART_1 = part_1.cpp
SOURCES_PART_2 = part_2.cpp
INC=-I../../lib

main:
	mkdir -p ${BINFOLDER}
	$(CXX) $(CXXFLAGS) ${INC} -o ${BINFOLDER}/part_1 ${SOURCES_PART_1}
	$(CXX) $(CXXFLAGS) ${INC} -o ${BINFOLDER}/part_2 ${SOURCES_PART_2}