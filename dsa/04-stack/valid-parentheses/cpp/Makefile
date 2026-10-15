CXX      ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan clean
test: ; @$(CXX) $(CXXFLAGS) -o /tmp/vpar_cpp test_solution.cpp && /tmp/vpar_cpp
asan: ; @$(CXX) $(CXXFLAGS) -g -fsanitize=address,undefined -o /tmp/vpar_cpp_asan test_solution.cpp && /tmp/vpar_cpp_asan
clean: ; @rm -f /tmp/vpar_cpp /tmp/vpar_cpp_asan
