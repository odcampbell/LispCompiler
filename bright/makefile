CXXFLAGS ?= -std=c++17 -g -Wall -Wextra -Werror

bright: bright.cpp scanner.cpp printer.cpp types.cpp
	$(CXX) $(CXXFLAGS)  -o $@ $^

clean:
	rm *.o *.exe