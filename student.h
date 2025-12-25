#ifndef STUDENT_H__
#define STUDENT_H__

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "size_limits.h"

bool date_check(char *date);

struct student_t
{
    char second_name[NAME_LEN];
    char first_name[NAME_LEN];
    char group[GROUP_LEN];
    bool is_male;
    size_t age;
    double avg_mark;
    char enter_date[DATE_LEN];
    int house_type;
    union address_t
    {
        struct home_address_t
        {
            char streat[STREAT_LEN];
            size_t house;
            size_t flat;
        } home;
        struct hostel_address_t
        {
            size_t house;
            size_t room;
        } hostel;
        struct rent_address_t
        {
            char streat[STREAT_LEN];
            size_t house;
            size_t flat;
            size_t cost;
        } rent;
    } address;
};

struct student_key_t
{
    size_t index;
    double avg_mark;
};

int read_input(struct student_t *cur_stud);
int read_from_txt(FILE *f, struct student_t *cur_stud);
bool is_year_equal(const struct student_t *cur_stud, size_t year);
void print_student(const struct student_t *stud, size_t index);

#endif