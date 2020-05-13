BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++17 -g

main:
	mkdir -p ${BINFOLDER}
	cp test.txt ${BINFOLDER}
	cp verify.txt ${BINFOLDER}
	$(CXX) $(CXXFLAGS) -o ${BINFOLDER}/main main.cpp