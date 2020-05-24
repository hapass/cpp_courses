BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++17 -g
SOURCES_PART_1 = group_by_prefix_part_1.cpp
SOURCES_PART_2 = group_by_prefix_part_2.cpp
INC=-I../../lib

main:
	mkdir -p ${BINFOLDER}
	$(CXX) $(CXXFLAGS) ${INC} -o ${BINFOLDER}/part_1 ${SOURCES_PART_1}
	$(CXX) $(CXXFLAGS) ${INC} -o ${BINFOLDER}/part_2 ${SOURCES_PART_2}