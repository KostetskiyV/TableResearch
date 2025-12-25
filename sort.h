#ifndef SORT_H__
#define SORT_H__

#include <stddef.h>
#include <time.h>

typedef int (*comparator_t)(const void *l, const void *r);

double calc_elapsed_time(const struct timespec *beg,
                         const struct timespec *end);

int cmp_students(const void *l, const void *r);
int cmp_student_keys(const void *l, const void *r);

double buble_sort(void *arr, size_t arr_n, size_t elem_size, comparator_t cmp);
double heap_sort(void *arr, size_t arr_n, size_t elem_size, comparator_t cmp);

#endif