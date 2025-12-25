#include <string.h>
#include <math.h>
#include "filter.h"

bool is_bool_equal(const void *l, const void *r)
{
    bool val1 = *((bool*) l);
    bool val2 = *((bool*) r);
    return val1 == val2;
}

bool is_int_equal(const void *l, const void *r)
{
    int num1 = *((int*) l);
    int num2 = *((int*) r);
    #include <stdio.h>
    printf("%d %d\n", num1, num2);
    return num1 == num2;
}

bool is_size_t_equal(const void *l, const void *r)
{
    size_t num1 = *((size_t*) l);
    size_t num2 = *((size_t*) r);
    return num1 == num2;
}

bool is_double_equal(const void *l, const void *r)
{
    double num1 = *((double*) l);
    double num2 = *((double*) r);
    return fabs(num1 - num2) < EPS;
}

bool is_string_equal(const void *l, const void *r)
{
    char *str1 = (char*) l;
    char *str2 = (char*) r;
    return strcmp(str1, str2) == 0;
}

void delete_by_field(struct student_t *students, size_t *table_range, void *value, size_t pdiff, is_equal_t is_equal)
{
    size_t deleted = 0;
    for (size_t i = 0; i < *table_range; i++)
    {
        struct student_t cur = students[i];
        void *cur_value = (char*) &cur + (char) pdiff;
        if (is_equal(cur_value, value))
            deleted++;
        else
            students[i - deleted] = cur;
    }
    (*table_range) -= deleted;
}
