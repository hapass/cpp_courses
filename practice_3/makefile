BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++17 -g

main:
	mkdir -p ${BINFOLDER}
	cp matrix.txt bin/matrix.txt
	$(CXX) $(CXXFLAGS) -o ${BINFOLDER}/main main.cpp