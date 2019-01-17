BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++11 -g

main:
	mkdir -p ${BINFOLDER}
	cp data.txt bin/data.txt
	$(CXX) $(CXXFLAGS) -o ${BINFOLDER}/main main.cpp