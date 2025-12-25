#ifndef ANALYTICS_H__
#define ANALYTICS_H__

#include <stddef.h>
#include "student.h"

#define ANALYZE_DOTS 10

void array_cp(void *src, void *dst, size_t elem_size, size_t elem_count);
void collect_analyze(struct student_t *students, struct student_key_t *keys, size_t table_range);

#endif