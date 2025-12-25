#ifndef MENU_ACTIONS_H__
#define MENU_ACTIONS_H__

#include <stddef.h>
#include "student.h"

#define FILE_SRC "students.txt"

void print_as_is(struct student_t *student, size_t table_range);
int add(struct student_t *students, struct student_key_t *keys, size_t *table_range);
int import_txt(struct student_t *students, struct student_key_t *keys, size_t *table_range);
int del(struct student_t *students, struct student_key_t *keys, size_t *table_range);
void show_sorted_keys(struct student_key_t *keys, size_t table_range);
void show_sorted_students(struct student_t *students, struct student_key_t *keys, size_t table_range);
void show_students_sorted_by_keys(struct student_t *students, struct student_key_t *keys, size_t table_range);
void show_filtered(const struct student_t *students, size_t table_range);
void analyze(struct student_t *students, struct student_key_t *keys, size_t table_range);

#endif