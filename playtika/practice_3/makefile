BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++11 -g

main:
	mkdir -p ${BINFOLDER}
	cp matrix.txt bin/matrix.txt
	$(CXX) $(CXXFLAGS) -o ${BINFOLDER}/main main.cpp