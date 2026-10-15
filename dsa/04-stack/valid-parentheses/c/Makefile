CC      ?= gcc
CFLAGS  ?= -std=c17 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan memcheck clean
test: ; @$(CC) $(CFLAGS) -o /tmp/vpar_c solution.c test_solution.c && /tmp/vpar_c
asan: ; @$(CC) $(CFLAGS) -g -fsanitize=address,undefined -o /tmp/vpar_c_asan solution.c test_solution.c && /tmp/vpar_c_asan
memcheck: ; @$(CC) $(CFLAGS) -g -o /tmp/vpar_c_mc solution.c test_solution.c && valgrind --error-exitcode=1 --leak-check=full /tmp/vpar_c_mc
clean: ; @rm -f /tmp/vpar_c /tmp/vpar_c_asan /tmp/vpar_c_mc
