CXX      ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan clean
test: ; @$(CXX) $(CXXFLAGS) -o /tmp/bs_cpp test_solution.cpp && /tmp/bs_cpp
asan: ; @$(CXX) $(CXXFLAGS) -g -fsanitize=address,undefined -o /tmp/bs_cpp_asan test_solution.cpp && /tmp/bs_cpp_asan
clean: ; @rm -f /tmp/bs_cpp /tmp/bs_cpp_asan
