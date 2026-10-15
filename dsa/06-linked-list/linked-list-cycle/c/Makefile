CC      ?= gcc
CFLAGS  ?= -std=c17 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan memcheck clean
test: ; @$(CC) $(CFLAGS) -o /tmp/llc_c solution.c test_solution.c && /tmp/llc_c
asan: ; @$(CC) $(CFLAGS) -g -fsanitize=address,undefined -o /tmp/llc_c_asan solution.c test_solution.c && /tmp/llc_c_asan
memcheck: ; @$(CC) $(CFLAGS) -g -o /tmp/llc_c_mc solution.c test_solution.c && valgrind --error-exitcode=1 --leak-check=full /tmp/llc_c_mc
clean: ; @rm -f /tmp/llc_c /tmp/llc_c_asan /tmp/llc_c_mc
