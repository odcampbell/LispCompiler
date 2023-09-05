CXXFLAGS ?= -g -Wall -Wextra -Werror

bright: bright.cpp token.o scanner.o 
	$(CXX) $(CXXFLAGS) bright.cpp token.o scanner.o -o run_bright

scanner.o: scanner.cpp tokenType.hpp

token.o: token.cpp tokenType.hpp

clean:
	rm *.o *.exe