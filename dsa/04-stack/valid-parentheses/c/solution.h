#ifndef VALID_PARENS_H
#define VALID_PARENS_H
#include <stddef.h>
/* 1 if s is a balanced, correctly nested sequence of ()[]{}, else 0. */
int is_valid(const char *s, size_t n);
#endif
