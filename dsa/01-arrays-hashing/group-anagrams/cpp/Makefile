CXX      ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan clean
test: ; @$(CXX) $(CXXFLAGS) -o /tmp/ga_cpp test_solution.cpp && /tmp/ga_cpp
asan: ; @$(CXX) $(CXXFLAGS) -g -fsanitize=address,undefined -o /tmp/ga_cpp_asan test_solution.cpp && /tmp/ga_cpp_asan
clean: ; @rm -f /tmp/ga_cpp /tmp/ga_cpp_asan
