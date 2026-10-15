CC      ?= gcc
CFLAGS  ?= -std=c17 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan memcheck clean
test: ; @$(CC) $(CFLAGS) -o /tmp/rl_c solution.c test_solution.c && /tmp/rl_c
asan: ; @$(CC) $(CFLAGS) -g -fsanitize=address,undefined -o /tmp/rl_c_asan solution.c test_solution.c && /tmp/rl_c_asan
memcheck: ; @$(CC) $(CFLAGS) -g -o /tmp/rl_c_mc solution.c test_solution.c && valgrind --error-exitcode=1 --leak-check=full /tmp/rl_c_mc
clean: ; @rm -f /tmp/rl_c /tmp/rl_c_asan /tmp/rl_c_mc
