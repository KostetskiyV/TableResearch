#ifndef TBL_FORMATTER_H__
#define TBL_FORMATTER_H__

#include <stddef.h>

char *gen_str(size_t len, char ch);

void print_str(const char *str, size_t field_len);
void print_pos_num(size_t num, size_t field_len);
void print_double(double time, size_t field_len);

#endif