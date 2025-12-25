#ifndef FILTER_H__
#define FILTER_H__

#include <stddef.h>
#include <stdbool.h>
#include "student.h"

#define EPS 1E-5

typedef bool (*is_equal_t)(const void *l, const void *r);

bool is_bool_equal(const void *l, const void *r);
bool is_int_equal(const void *l, const void *r);
bool is_size_t_equal(const void *l, const void *r);
bool is_double_equal(const void *l, const void *r);
bool is_string_equal(const void *l, const void *r);

void delete_by_field(struct student_t *students, size_t *table_range, void *value, size_t pdiff, is_equal_t is_equal);

#endif