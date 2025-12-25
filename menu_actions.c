#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "menu_actions.h"
#include "student.h"
#include "sort.h"
#include "filter.h"
#include "analytics.h"
#include "tbl_printer.h"
#include "tbl_formatter.h"
#include "error_codes.h"

void print_as_is(struct student_t *students, size_t table_range)
{
    print_students_header(false);
    print_students(students, table_range);
}

int add(struct student_t *students, struct student_key_t *keys, size_t *table_range)
{
    if (*table_range + 1 == TABLE_RANGE)
    {
        printf("Количество элементов таблицы максимально\n");
        return OK;
    }
    char buf[3];
    fgets(buf, sizeof(buf), stdin);
    int rc = read_input(&(students[*table_range]));
    if (rc != OK)
        return rc;
    keys[*table_range].index = *table_range;
    keys[*table_range].avg_mark = students[*table_range].avg_mark;
    (*table_range)++;

    return OK;
}

int import_txt(struct student_t *students, struct student_key_t *keys, size_t *table_range)
{
    FILE *f = fopen(FILE_SRC, "r");
    int rc = OK;
    if (!f)
        return ERR_OPEN;
    *table_range = 0;
    for (size_t i = 0; rc == OK; i++, (*table_range)++)
    {
        if (rc == OK && i == TABLE_RANGE)
            rc = ERR_TABLE_OVERFLOW;
        
        if (rc == OK)
            rc = read_from_txt(f, &(students[i]));
        if (rc == OK)
        {
            keys[i].index = i;
            keys[i].avg_mark = students[i].avg_mark;
        }
    }

    fclose(f);
    if (rc != END_OF_FILE)
        return rc;
    (*table_range)--;
    return OK;
}

int del(struct student_t *students, struct student_key_t *keys, size_t *table_range)
{
    if (*table_range == 0)
    {
        printf("Нечего удалять, таблица пуста\n");
        return OK;
    }

    char input_buf[15];
    char *p;
    fgets(input_buf, sizeof(input_buf), stdin);

    printf("Введите поле удаления (index, second_name, first_name, group, is_male, age, avg_mark, home, hostel, rent):\n");
    if (!fgets(input_buf, sizeof(input_buf), stdin))
        return ERR_IO;
    p = strrchr(input_buf, '\n');
    if (p)
        *p = 0;
    else
        return ERR_LINE_BUFFER_TOO_SMALL;
    
    if (strcmp(input_buf, "index") == 0)
    {
        size_t value;
        printf("Введите индекс удаляемого элемента:\n");
        if (scanf("%lu", &value) != 1)
            return ERR_IO;
        if (value < 1 || value > *table_range)
            return ERR_RANGE;
        fgets(input_buf, sizeof(input_buf), stdin);
        for (size_t i = value; i < *table_range; i++)
            students[i - 1] = students[i];
        (*table_range)--;
    }
    else if (strcmp(input_buf, "second_name") == 0)
    {
        char value[20];
        printf("Введите фамилию удаляемого(-ых) студента(-ов):\n");
        if (!fgets(value, sizeof(value), stdin))
            return ERR_IO;
        p = strrchr(value, '\n');
        if (p)
            *p = 0;
        else
            return ERR_LINE_BUFFER_TOO_SMALL;
        delete_by_field(students, table_range, (void*) value, 0, is_string_equal);
    }
    else if (strcmp(input_buf, "first_name") == 0)
    {
        char value[20];
        size_t pdiff = offsetof(struct student_t, first_name);
        printf("Введите имя удаляемого(-ых) студента(-ов):\n");
        if (!fgets(value, sizeof(value), stdin))
            return ERR_IO;
        p = strrchr(value, '\n');
        if (p)
            *p = 0;
        else
            return ERR_LINE_BUFFER_TOO_SMALL;
        delete_by_field(students, table_range, (void*) value, pdiff, is_string_equal);
    }
    else if (strcmp(input_buf, "group") == 0)
    {
        char value[20];
        size_t pdiff = offsetof(struct student_t, group);
        printf("Введите группу удаляемого(-ых) студента(-ов):\n");
        if (!fgets(value, sizeof(value), stdin))
            return ERR_IO;
        p = strrchr(value, '\n');
        if (p)
            *p = 0;
        else
            return ERR_LINE_BUFFER_TOO_SMALL;
        delete_by_field(students, table_range, (void*) value, pdiff, is_string_equal);
    }
    else if (strcmp(input_buf, "is_male") == 0)
    {
        bool value;
        size_t pdiff = offsetof(struct student_t, is_male);
        printf("Введите пол удаляемого(-ых) студента(-ов) (m/f):\n");
        if (!fgets(input_buf, sizeof(input_buf), stdin))
            return ERR_IO;
        p = strrchr(input_buf, '\n');
        if (p)
            *p = 0;
        else
            return ERR_LINE_BUFFER_TOO_SMALL;

        if (strlen(input_buf) == 1 && input_buf[0] == 'm')
            value = true;
        else if (strlen(input_buf) == 1 && input_buf[0] == 'f')
            value = true;
        else
            return ERR_RANGE;
        delete_by_field(students, table_range, (void*) &value, pdiff, is_bool_equal);
    }
    else if (strcmp(input_buf, "age") == 0)
    {
        size_t value, pdiff = offsetof(struct student_t, age);
        printf("Введите возраст удаляемого(-ых) студента(-ов):\n");
        if (scanf("%lu", &value) != 1)
            return ERR_IO;
        fgets(input_buf, sizeof(input_buf), stdin);
        delete_by_field(students, table_range, (void*) &value, pdiff, is_size_t_equal);
    }
    else if (strcmp(input_buf, "avg_mark") == 0)
    {
        double value;
        size_t pdiff = offsetof(struct student_t, avg_mark);
        printf("Введите среднюю оценку удаляемого(-ых) студента(-ов):\n");
        if (scanf("%lf", &value) != 1)
            return ERR_IO;
        fgets(input_buf, sizeof(input_buf), stdin);
        delete_by_field(students, table_range, (void*) &value, pdiff, is_double_equal);
    }
    else if (strcmp(input_buf, "home") == 0)
    {
        int value = 1, pdiff = offsetof(struct student_t, house_type);
        delete_by_field(students, table_range, (void*) &value, pdiff, is_int_equal);
    }
    else if (strcmp(input_buf, "hostel") == 0)
    {
        int value = 2, pdiff = offsetof(struct student_t, house_type);
        delete_by_field(students, table_range, (void*) &value, pdiff, is_int_equal);
    }
    else if (strcmp(input_buf, "rent") == 0)
    {
        int value = 3, pdiff = offsetof(struct student_t, house_type);
        delete_by_field(students, table_range, (void*) &value, pdiff, is_int_equal);
    }
    else
    {
        printf("Введено несуществующее поле!\n");
        return OK;
    }

    for (size_t i = 0; i < *table_range; i++)
    {
        keys[i].index = i;
        keys[i].avg_mark = students[i].avg_mark;
    }
    return OK;
}

void show_sorted_keys(struct student_key_t *keys, size_t table_range)
{
    if (table_range == 0)
        return;
    double time = buble_sort(keys, table_range, sizeof(keys[0]), cmp_student_keys);
    printf("\n-- sort time: %lf --\n\n", time);
    print_keys_header(true);
    print_keys(keys, table_range);
}

void show_sorted_students(struct student_t *students, struct student_key_t *keys, size_t table_range)
{
    if (table_range == 0)
        return;
    double time = heap_sort(students, table_range, sizeof(students[0]), cmp_students);
    printf("\n-- sort time: %lf --\n\n", time);
    print_students_header(true);
    print_students(students, table_range);
    for (size_t i = 0; i < table_range; i++)
    {
        keys[i].index = i;
        keys[i].avg_mark = students[i].avg_mark;
    }
}

void show_students_sorted_by_keys(struct student_t *students, struct student_key_t *keys, size_t table_range)
{
    if (table_range == 0)
        return;
    double time = buble_sort(keys, table_range, sizeof(keys[0]), cmp_student_keys);
    printf("\n-- sort time: %lf --\n\n", time);
    print_students_header(true);
    print_students_by_keys(students, keys, table_range);
}

void show_filtered(const struct student_t *students, size_t table_range)
{
    if (table_range == 0)
        return;
    size_t year, cost;
    
    printf("Введите искомый год поступления (1900-2025):\n");
    if (scanf("%lu", &year) != 1)
    {
        printf("Некорректный формат ввода!\n");
        return;
    }
    if (year < 1900 || year > 2025)
    {
        printf("Год указан неверно!\n");
        return;
    }

    printf("Введите максимальную стоимость жилья (3000-50000):\n");
    if (scanf("%lu", &cost) != 1)
    {
        printf("Некорректный формат ввода!\n");
        return;
    }
    if (cost < 3000 || cost > 50000)
    {
        printf("Цена указана неверно!\n");
        return;
    }

    print_students_header(false);
    for (size_t i = 0; i < table_range; i++)
    {
        struct student_t cur_stud = students[i];
        if (cur_stud.house_type == 3 && cur_stud.address.rent.cost <= cost && is_year_equal(&cur_stud, year))
            print_student(&cur_stud, i);
    }
}

void analyze(struct student_t *students, struct student_key_t *keys, size_t table_range)
{
    if (table_range < ANALYZE_DOTS)
    {
        printf("Слишком мало строк для анализа!\n");
        return;
    }

    print_measures_header();
    collect_analyze(students, keys, table_range);
}