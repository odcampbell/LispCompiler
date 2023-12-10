CXXFLAGS ?= -std=c++17 -g -Wall -Wextra -Werror

bright: bright.cpp scanner.cpp printer.cpp types.cpp core.cpp
	$(CXX) $(CXXFLAGS)  -o $@ $^

clean:
	rm  *.exe #*.o