CXX      ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan clean
test: ; @$(CXX) $(CXXFLAGS) -o /tmp/cs_cpp test_solution.cpp && /tmp/cs_cpp
asan: ; @$(CXX) $(CXXFLAGS) -g -fsanitize=address,undefined -o /tmp/cs_cpp_asan test_solution.cpp && /tmp/cs_cpp_asan
clean: ; @rm -f /tmp/cs_cpp /tmp/cs_cpp_asan
