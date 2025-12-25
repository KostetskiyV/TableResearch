#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sort.h"
#include "analytics.h"
#include "tbl_formatter.h"
#include "size_limits.h"

#define FILE_RESULTS "graph/measures.txt"

void array_cp(void *src, void *dst, size_t elem_size, size_t elem_count)
{
    for (size_t i = 0; i < elem_count; i++)
        memcpy(dst, src, elem_size);
}

void collect_analyze(struct student_t *students, struct student_key_t *keys, size_t table_range)
{
    FILE *out_measures = fopen(FILE_RESULTS, "w");
    struct timespec start, end;
    struct student_t *cur_students = NULL;
    struct student_key_t *cur_keys = NULL;

    cur_students = malloc(TABLE_RANGE * sizeof(struct student_t));
    if (cur_students == NULL)
    {
        printf("Can`t allocate memory!\n");
        return;
    }
    cur_keys = malloc(TABLE_RANGE * sizeof(struct student_key_t));
    if (cur_keys == NULL)
    {
        printf("Can`t allocate memory!\n");
        return;
    }

    array_cp(students, cur_students, sizeof(students[0]), table_range);
    array_cp(keys, cur_keys, sizeof(keys[0]), table_range);

    for (size_t cur_range = 1, step = (table_range - 1) / ANALYZE_DOTS + 1; cur_range < table_range; cur_range += step)
    {
        double time1, time2, time3, time4;
        print_pos_num(cur_range, 17);
        printf("|");

        time1 = buble_sort(cur_students, cur_range, sizeof(students[0]), cmp_students);
        print_double(time1, 24);
        printf("|");
        array_cp(students, cur_students, sizeof(students[0]), cur_range);

        time2 = heap_sort(cur_students, cur_range, sizeof(students[0]), cmp_students);
        print_double(time2, 18);
        printf("|");
        array_cp(students, cur_students, sizeof(students[0]), cur_range);

        time3 = buble_sort(cur_keys, cur_range, sizeof(keys[0]), cmp_student_keys);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        array_cp(keys, cur_keys, sizeof(keys[0]), cur_range);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        time3 += calc_elapsed_time(&start, &end);
        print_double(time3, 24);
        printf("|");

        time4 = heap_sort(cur_keys, cur_range, sizeof(keys[0]), cmp_student_keys);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        array_cp(keys, cur_keys, sizeof(keys[0]), cur_range);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        time4 += calc_elapsed_time(&start, &end);
        print_double(time4, 18);
        printf("\n");

        if (out_measures)
            fprintf(out_measures, "%lu %lf %lf %lf %lf\n", cur_range, time1, time2, time3, time4);
    }
    double time1, time2, time3, time4;
    print_pos_num(table_range, 17);
    printf("|");

    time1 = buble_sort(cur_students, table_range, sizeof(students[0]), cmp_students);
    print_double(time1, 24);
    printf("|");
    array_cp(students, cur_students, sizeof(students[0]), table_range);

    time2 = heap_sort(cur_students, table_range, sizeof(students[0]), cmp_students);
    print_double(time2, 18);
    printf("|");

    time3 = buble_sort(cur_keys, table_range, sizeof(keys[0]), cmp_student_keys);
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    array_cp(keys, cur_keys, sizeof(keys[0]), table_range);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    time3 += calc_elapsed_time(&start, &end);
    print_double(time3, 24);
    printf("|");

    time4 = heap_sort(cur_keys, table_range, sizeof(keys[0]), cmp_student_keys);
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    array_cp(keys, cur_keys, sizeof(keys[0]), table_range);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    time4 += calc_elapsed_time(&start, &end);
    print_double(time4, 18);
    printf("\n");

    free(cur_students);
    free(cur_keys);

    if (out_measures)
    {
        fprintf(out_measures, "%lu %lf %lf %lf %lf\n", table_range, time1, time2, time3, time4);
        fclose(out_measures);
    }
}