CC      ?= gcc
CFLAGS  ?= -std=c17 -Wall -Wextra -Wpedantic -O2
.PHONY: test asan memcheck clean
test: ; @$(CC) $(CFLAGS) -o /tmp/vp_c solution.c test_solution.c && /tmp/vp_c
asan: ; @$(CC) $(CFLAGS) -g -fsanitize=address,undefined -o /tmp/vp_c_asan solution.c test_solution.c && /tmp/vp_c_asan
memcheck: ; @$(CC) $(CFLAGS) -g -o /tmp/vp_c_mc solution.c test_solution.c && valgrind --error-exitcode=1 --leak-check=full /tmp/vp_c_mc
clean: ; @rm -f /tmp/vp_c /tmp/vp_c_asan /tmp/vp_c_mc
