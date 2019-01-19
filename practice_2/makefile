BINFOLDER = bin

CXX = clang++
CXXFLAGS = -std=c++11 -g

main:
	mkdir -p ${BINFOLDER}
	cp cities.txt bin/cities.txt
	cp words.txt bin/words.txt
	$(CXX) $(CXXFLAGS) -o ${BINFOLDER}/main main.cpp