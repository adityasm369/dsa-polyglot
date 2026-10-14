CXX      ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan clean
test: ; @$(CXX) $(CXXFLAGS) -o /tmp/ts_cpp test_solution.cpp && /tmp/ts_cpp
asan: ; @$(CXX) $(CXXFLAGS) -g -fsanitize=address,undefined -o /tmp/ts_cpp_asan test_solution.cpp && /tmp/ts_cpp_asan
clean: ; @rm -f /tmp/ts_cpp /tmp/ts_cpp_asan
