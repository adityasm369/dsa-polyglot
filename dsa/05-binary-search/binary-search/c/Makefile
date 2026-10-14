CC      ?= gcc
CFLAGS  ?= -std=c17 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan memcheck clean
test: ; @$(CC) $(CFLAGS) -o /tmp/bs_c solution.c test_solution.c && /tmp/bs_c
asan: ; @$(CC) $(CFLAGS) -g -fsanitize=address,undefined -o /tmp/bs_c_asan solution.c test_solution.c && /tmp/bs_c_asan
memcheck: ; @$(CC) $(CFLAGS) -g -o /tmp/bs_c_mc solution.c test_solution.c && valgrind --error-exitcode=1 --leak-check=full /tmp/bs_c_mc
clean: ; @rm -f /tmp/bs_c /tmp/bs_c_asan /tmp/bs_c_mc
