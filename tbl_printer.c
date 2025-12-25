#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "tbl_printer.h"
#include "tbl_formatter.h"

void print_students_header(bool sorted)
{
    if (sorted)
        printf("                                                                           V\n");
    printf("Индекс  |      Фамилия       |        Имя         |Группа |Пол|Возраст|Ср. оценка|Дата поступления| Адрес\n");
    printf("=============================================================================================================================\n");
}

void print_keys_header()
{
    printf("            V\n");
    printf("Индекс|Ср. оценка\n");
    printf("=================\n");
}

void print_measures_header()
{
    printf("                 |     Без использования таблицы ключей      |      С применением таблицы ключей\n");
    printf("--------------------------------------------------------------------------------------------------------\n");
    printf("Кол-во элементов | Пузырьковая сортировка | Сортировка кучей | Пузырьковая сортировка | Сортировка кучей \n");
    printf("========================================================================================================\n");
}

void print_students(struct student_t *students, size_t table_range)
{
    for (size_t i = 0; i < table_range; i++)
        print_student(&(students[i]), i);
}

void print_students_by_keys(struct student_t *students, struct student_key_t *keys, size_t table_range)
{
    for (size_t i = 0; i < table_range; i++)
        print_student(&(students[keys[i].index]), keys[i].index);
}

void print_keys(struct student_key_t *keys, size_t table_range)
{
    for (size_t i = 0; i < table_range; i++)
    {
        size_t index = keys[i].index;
        print_pos_num(index, 6);
        printf("|%lf\n", keys[i].avg_mark);
        printf("-----------------\n");
    }
}
