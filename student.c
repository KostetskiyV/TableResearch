#include <string.h>
#include "student.h"
#include "tbl_formatter.h"
#include "date_check.h"
#include "error_codes.h"

int read_input(struct student_t *cur_stud)
{
    char *p;
    char buf[3];
    printf("Введите фамилию студента (до 20 символов):\n");
    if (!fgets(cur_stud->second_name, sizeof(cur_stud->second_name), stdin))
        return ERR_IO;
    p = strrchr(cur_stud->second_name, '\n');
    if (p)
        *p = 0;
    else
        return ERR_LINE_BUFFER_TOO_SMALL;

    printf("Введите имя студента (до 20 символов):\n");
    if (!fgets(cur_stud->first_name, sizeof(cur_stud->first_name), stdin))
        return ERR_IO;
    p = strrchr(cur_stud->first_name, '\n');
    if (p)
        *p = 0;
    else
        return ERR_LINE_BUFFER_TOO_SMALL;

    printf("Введите группу студента (до 7 символов):\n");
    if (!fgets(cur_stud->group, sizeof(cur_stud->group), stdin))
        return ERR_IO;
    p = strrchr(cur_stud->group, '\n');
    if (p)
        *p = 0;
    else
        return ERR_LINE_BUFFER_TOO_SMALL;

    printf("Введите пол студента (m/f):\n");
    if (!fgets(buf, sizeof(buf), stdin))
        return ERR_IO;
    p = strrchr(buf, '\n');
    if (p)
        *p = 0;
    else
        return ERR_LINE_BUFFER_TOO_SMALL;
    if (strlen(buf) == 1 && buf[0] == 'm')
        cur_stud->is_male = true;
    else if (strlen(buf) == 1 && buf[0] == 'f')
        cur_stud->is_male = false;
    else
        return ERR_IO;

    printf("Введите возраст студента (10 - 40):\n");
    if (scanf("%lu", &(cur_stud->age)) != 1)
        return ERR_IO;
    if (cur_stud->age < 10 || cur_stud->age > 40)
        return ERR_RANGE;

    printf("Введите средний балл студента (1.0 - 5.0):\n");
    if (scanf("%lf", &(cur_stud->avg_mark)) != 1)
        return ERR_IO;
    if (cur_stud->avg_mark < 1.0 || cur_stud->avg_mark > 5.0)
        return ERR_RANGE;
    fgets(buf, sizeof(buf), stdin);

    printf("Введите дату поступления (DD-MM-YYYY):\n");
    if (!fgets(cur_stud->enter_date, sizeof(cur_stud->enter_date), stdin))
        return ERR_IO;
    p = strrchr(cur_stud->enter_date, '\n');
    if (p)
        *p = 0;
    else
        return ERR_LINE_BUFFER_TOO_SMALL;
    if (!date_check(cur_stud->enter_date))
        return ERR_WRONG_DATE;

    printf("Введите тип адреса (1 - дом, 2 - общежитие, 3 - съёмное жильё):\n");
    if (scanf("%d", &(cur_stud->house_type)) != 1)
        return ERR_IO;
    if (cur_stud->house_type != 1 && cur_stud->house_type != 2 && cur_stud->house_type != 3)
        return ERR_RANGE;
    fgets(buf, sizeof(buf), stdin);

    if (cur_stud->house_type == 1)
    {
        printf("Введите улицу (до 20 символов):\n");
        if (!fgets(cur_stud->address.home.streat, sizeof(cur_stud->address.home.streat), stdin))
            return ERR_IO;
        p = strrchr(cur_stud->address.home.streat, '\n');
        if (p)
            *p = 0;
        else
            return ERR_LINE_BUFFER_TOO_SMALL;

        printf("Введите номер дома:\n");
        if (scanf("%lu", &(cur_stud->address.home.house)) != 1)
            return ERR_IO;
        if (cur_stud->address.home.house == 0)
            return ERR_RANGE;

        printf("Введите номер квартиры:\n");
        if (scanf("%lu", &(cur_stud->address.home.flat)) != 1)
            return ERR_IO;
        if (cur_stud->address.home.flat == 0)
            return ERR_RANGE;
    }
    else if (cur_stud->house_type == 2)
    {
        printf("Введите номер общежития:\n");
        if (scanf("%lu", &(cur_stud->address.hostel.house)) != 1)
            return ERR_IO;
        if (cur_stud->address.hostel.house == 0)
            return ERR_RANGE;

        printf("Введите номер комнаты:\n");
        if (scanf("%lu", &(cur_stud->address.hostel.room)) != 1)
            return ERR_IO;
        if (cur_stud->address.hostel.room == 0)
            return ERR_RANGE;
    }
    else
    {
        printf("Введите улицу (до 20 символов):\n");
        if (!fgets(cur_stud->address.rent.streat, sizeof(cur_stud->address.rent.streat), stdin))
            return ERR_IO;
        p = strrchr(cur_stud->address.rent.streat, '\n');
        if (p)
            *p = 0;
        else
            return ERR_LINE_BUFFER_TOO_SMALL;

        printf("Введите номер дома:\n");
        if (scanf("%lu", &(cur_stud->address.rent.house)) != 1)
            return ERR_IO;
        if (cur_stud->address.rent.house == 0)
            return ERR_RANGE;

        printf("Введите номер квартиры:\n");
        if (scanf("%lu", &(cur_stud->address.rent.flat)) != 1)
            return ERR_IO;
        if (cur_stud->address.rent.flat == 0)
            return ERR_RANGE;

        printf("Введите стоимость снимаемой квартиры:\n");
        if (scanf("%lu", &(cur_stud->address.rent.cost)) != 1)
            return ERR_IO;
        if (cur_stud->address.rent.cost == 0)
            return ERR_RANGE;
    }
    return OK;
}

int read_from_txt(FILE *f, struct student_t *cur_stud)
{
    char buf[100];
    char *p;

    if (!fgets(cur_stud->second_name, sizeof(cur_stud->second_name), f))
        return END_OF_FILE;
    p = strrchr(cur_stud->second_name, '\n');
    if (p)
        *p = 0;
    else
        return ERR_LINE_BUFFER_TOO_SMALL;
    if (strlen(cur_stud->second_name) == 0)
        return END_OF_FILE;

    if (!fgets(cur_stud->first_name, sizeof(cur_stud->first_name), f))
        return ERR_IO;
    p = strrchr(cur_stud->first_name, '\n');
    if (p)
        *p = 0;
    else
        return ERR_LINE_BUFFER_TOO_SMALL;
    if (strlen(cur_stud->first_name) == 0)
        return ERR_IO;

    if (!fgets(cur_stud->group, sizeof(cur_stud->group), f))
        return ERR_IO;
    p = strrchr(cur_stud->group, '\n');
    if (p)
        *p = 0;
    else
        return ERR_LINE_BUFFER_TOO_SMALL;
    if (strlen(cur_stud->group) == 0)
        return ERR_IO;

    if (!fgets(buf, sizeof(buf), f))
        return ERR_IO;
    p = strrchr(buf, '\n');
    if (p)
        *p = 0;
    else
        return ERR_LINE_BUFFER_TOO_SMALL;
    if (strlen(buf) != 1 || (buf[0] != 'm' && buf[0] != 'f'))
        return ERR_IO;
    cur_stud->is_male = (buf[0] == 'm');

    if (fscanf(f, "%lu%lf", &(cur_stud->age), &(cur_stud->avg_mark)) != 2)
        return ERR_IO;
    if (cur_stud->avg_mark < 1 || cur_stud->avg_mark > 5 || cur_stud->age < 9 || cur_stud->age > 40)
        return ERR_RANGE;
    fgets(buf, sizeof(buf), f);

    if (!fgets(cur_stud->enter_date, sizeof(cur_stud->enter_date), f))
        return ERR_IO;
    p = strrchr(cur_stud->enter_date, '\n');
    if (p)
        *p = 0;
    else
        return ERR_LINE_BUFFER_TOO_SMALL;
    if (strlen(cur_stud->enter_date) == 0)
        return ERR_IO;

    if (fscanf(f, "%d", &(cur_stud->house_type)) != 1)
        return ERR_IO;
    if (cur_stud->house_type != 1 && cur_stud->house_type != 2 && cur_stud->house_type != 3)
        return ERR_RANGE;
    fgets(buf, sizeof(buf), f);

    if (cur_stud->house_type == 1)
    {
        if (!fgets(cur_stud->address.home.streat, sizeof(cur_stud->address.home.streat), f))
            return ERR_IO;
        p = strrchr(cur_stud->address.home.streat, '\n');
        if (p)
            *p = 0;
        else
            return ERR_LINE_BUFFER_TOO_SMALL;
        if (strlen(cur_stud->address.home.streat) == 0)
            return ERR_IO;

        if (fscanf(f, "%lu%lu", &(cur_stud->address.home.house), &(cur_stud->address.home.flat)) != 2)
            return ERR_IO;
        fgets(buf, sizeof(buf), f);
    }
    else if (cur_stud->house_type == 2)
    {
        if (fscanf(f, "%lu%lu", &(cur_stud->address.hostel.house), &(cur_stud->address.hostel.room)) != 2)
            return ERR_IO;
        fgets(buf, sizeof(buf), f);
    }
    else
    {
        if (!fgets(cur_stud->address.rent.streat, sizeof(cur_stud->address.rent.streat), f))
            return ERR_IO;
        p = strrchr(cur_stud->address.rent.streat, '\n');
        if (p)
            *p = 0;
        else
            return ERR_LINE_BUFFER_TOO_SMALL;
        if (strlen(cur_stud->address.rent.streat) == 0)
            return ERR_IO;

        if (fscanf(f, "%lu%lu%lu", &(cur_stud->address.rent.house), &(cur_stud->address.rent.flat), &(cur_stud->address.rent.cost)) != 3)
            return ERR_IO;
        fgets(buf, sizeof(buf), f);
    }
    if (!date_check(cur_stud->enter_date))
        return ERR_WRONG_DATE;
    
    return OK;
}

bool is_year_equal(const struct student_t *cur_stud, size_t year)
{
    size_t stud_year = 0;
    for (size_t i = 6; i < 10; i++)
    {
        stud_year *= 10;
        stud_year += (cur_stud->enter_date[i] - '0');
    }
    return stud_year == year;
}

void print_student(const struct student_t *stud, size_t index)
{
    print_pos_num(index, 8);
    printf("|");
    print_str(stud->second_name, 20);
    print_str(stud->first_name, 20);
    print_str(stud->group, 7);
    printf(stud->is_male ? " м |" : " ж |");
    printf("  %lu   |", stud->age);
    printf(" %.6f |", stud->avg_mark);
    printf("   %s   |", stud->enter_date);

    if (stud->house_type == 1)
        printf("ул. %s, д%lu, кв. %lu", stud->address.home.streat, stud->address.home.house, stud->address.home.flat);
    else if (stud->house_type == 2)
        printf("Хостел №%lu, комната %lu", stud->address.hostel.house, stud->address.hostel.room);
    else
        printf("ул. %s, д%lu, кв. %lu, стоимость %luр.", stud->address.rent.streat, stud->address.rent.house, stud->address.rent.flat, stud->address.rent.cost);
    
    printf("\n-----------------------------------------------------------------------------------------------------------------------------\n");
}