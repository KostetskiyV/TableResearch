#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "menu_actions.h"
#include "student.h"
#include "size_limits.h"
#include "error_codes.h"

#define END_MODE 0
#define PRINT_MODE 1
#define ADD_MODE 2
#define IMPORT_TXT_MODE 3
#define DELETE_MODE 4
#define SHOW_KEYS_MODE 5
#define SHOW_SORTED_MODE 6
#define SHOW_SORTED_BY_KEYS_MODE 7
#define PRINT_FILTERED_MODE 8
#define ANALYZE_MODE 9

void print_menu()
{
    printf("Наберите 1, чтобы вывести студентов неотсортированными\n");
    printf("Наберите 2, чтобы добавить студента\n");
    printf("Наберите 3, чтобы импортировать записи из students.txt\n");
    printf("Наберите 4, чтобы удалить студента\n");
    printf("Наберите 5, чтобы просмотреть отсортированную таблицу ключей\n");
    printf("Наберите 6, чтобы просмотреть отсортированную исходную таблицу\n");
    printf("Наберите 7, чтобы просмотреть отсортированную таблицу с использованием таблицы ключей\n");
    printf("Наберите 8, чтобы просмотреть студентов по году поступления снимающих квартиру стоимостью меньше указанной\n");
    printf("Наберите 9, чтобы анализиривать время выполнения\n");
    printf("Наберите 0, чтобы завершить\n");
}

int main(void)
{
    int rc = OK;
    size_t table_range = 0;
    struct student_t *students_tbl = NULL;
    struct student_key_t *students_key_tbl = NULL;

    students_tbl = malloc(TABLE_RANGE * sizeof(struct student_t));
    if (students_tbl == NULL)
    {
        printf("Can`t allocate memory!\n");
        return ERR_MEM;
    }
    students_key_tbl = malloc(TABLE_RANGE * sizeof(struct student_key_t));
    if (students_key_tbl == NULL)
    {
        printf("Can`t allocate memory!\n");
        return ERR_MEM;
    }

    while (rc == OK)
    {
        int mode;
        print_menu();
        if (rc == OK && scanf("%d", &mode) != 1)
            rc = ERR_IO;
        if (mode == END_MODE)
            break;
        if (rc == OK)
        {
            switch (mode)
            {
                case PRINT_MODE:
                    print_as_is(students_tbl, table_range);
                    break;
                case ADD_MODE:
                    rc = add(students_tbl, students_key_tbl, &table_range);
                    break;
                case IMPORT_TXT_MODE:
                    rc = import_txt(students_tbl, students_key_tbl, &table_range);
                    break;
                case DELETE_MODE:
                    rc = del(students_tbl, students_key_tbl, &table_range);
                    break;
                case SHOW_KEYS_MODE:
                    show_sorted_keys(students_key_tbl, table_range);
                    break;
                case SHOW_SORTED_MODE:
                    show_sorted_students(students_tbl, students_key_tbl, table_range);
                    break;
                case SHOW_SORTED_BY_KEYS_MODE:
                    show_students_sorted_by_keys(students_tbl, students_key_tbl, table_range);
                    break;
                case PRINT_FILTERED_MODE:
                    show_filtered(students_tbl, table_range);
                    break;
                case ANALYZE_MODE:
                    analyze(students_tbl, students_key_tbl, table_range);
                    break;
                default:
                    rc = ERR_MODE;
            }
        }
    }

    free(students_tbl);
    free(students_key_tbl);

    if (rc == ERR_IO)
        printf("Ошибка формата данных\n");
    else if (rc == ERR_OPEN)
        printf("Ошибка открытия файла\n");
    else if (rc == ERR_RANGE)
        printf("Ошибка интервала данных\n");
    else if (rc == ERR_MODE)
        printf("Неправильный ввод меню\n");
    else if (rc == ERR_LINE_BUFFER_TOO_SMALL)
        printf("Введён слишком длинный текст\n");
    else if (rc == ERR_TABLE_OVERFLOW)
        printf("Переполнена таблица\n");
    else if (rc == ERR_WRONG_DATE)
        printf("Формат даты некорректный\n");

    return rc;
}