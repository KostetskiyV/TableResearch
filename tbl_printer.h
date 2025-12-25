#ifndef TBL_PRINTER_H__
#define TBL_PRINTER_H__

#include <stddef.h>
#include <stdbool.h>
#include "student.h"

void print_students_header(bool sorted);
void print_keys_header();
void print_measures_header();

void print_students(struct student_t *students, size_t table_range);
void print_students_by_keys(struct student_t *students, struct student_key_t *keys, size_t table_range);
void print_keys(struct student_key_t *keys, size_t table_range);

#endif