CXX      ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan clean
test: ; @$(CXX) $(CXXFLAGS) -o /tmp/rl_cpp test_solution.cpp && /tmp/rl_cpp
asan: ; @$(CXX) $(CXXFLAGS) -g -fsanitize=address,undefined -o /tmp/rl_cpp_asan test_solution.cpp && /tmp/rl_cpp_asan
clean: ; @rm -f /tmp/rl_cpp /tmp/rl_cpp_asan
