CXX      ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan clean
test: ; @$(CXX) $(CXXFLAGS) -o /tmp/vp_cpp test_solution.cpp && /tmp/vp_cpp
asan: ; @$(CXX) $(CXXFLAGS) -g -fsanitize=address,undefined -o /tmp/vp_cpp_asan test_solution.cpp && /tmp/vp_cpp_asan
clean: ; @rm -f /tmp/vp_cpp /tmp/vp_cpp_asan
