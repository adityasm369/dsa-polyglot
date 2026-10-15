CXX      ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan clean
test: ; @$(CXX) $(CXXFLAGS) -o /tmp/llc_cpp test_solution.cpp && /tmp/llc_cpp
asan: ; @$(CXX) $(CXXFLAGS) -g -fsanitize=address,undefined -o /tmp/llc_cpp_asan test_solution.cpp && /tmp/llc_cpp_asan
clean: ; @rm -f /tmp/llc_cpp /tmp/llc_cpp_asan
