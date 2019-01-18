BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++17 -g

main:
	mkdir -p ${BINFOLDER}
	cp cities.txt bin/cities.txt
	cp words.txt bin/words.txt
	cp matrix.txt bin/matrix.txt
	$(CXX) $(CXXFLAGS) -o ${BINFOLDER}/main main.cpp