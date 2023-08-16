CXX=g++
CXXFLAGS=-Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror -std=c++20
SRCS=main.cpp

all: main

main: $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o main

clean:
	rm -f main
