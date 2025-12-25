#include <string.h>
#include "student.h"
#include "sort.h"

double calc_elapsed_time(const struct timespec *beg,
                         const struct timespec *end) {
    return ((end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 +
        (end->tv_nsec - beg->tv_nsec)) /
        1000.0 / 1000.0 / 1000.0;
}


int cmp_students(const void *l, const void *r)
{
    struct student_t* stud1 = (struct student_t*)l;
    struct student_t* stud2 = (struct student_t*)r;
    if (stud1->avg_mark > stud2->avg_mark)
        return 1;
    else if (stud1->avg_mark < stud2->avg_mark)
        return -1;
    return 0;
}

int cmp_student_keys(const void *l, const void *r)
{
    struct student_key_t* stud1 = (struct student_key_t*)l;
    struct student_key_t* stud2 = (struct student_key_t*)r;
    if (stud1->avg_mark > stud2->avg_mark)
        return 1;
    else if (stud1->avg_mark < stud2->avg_mark)
        return -1;
    return 0;
}

void swap(void *l, void *r, size_t elem_size)
{
    char tmp[elem_size];
    memcpy(tmp, l, elem_size);
    memcpy(l, r, elem_size);
    memcpy(r, tmp, elem_size);
}

double buble_sort(void *arr, size_t arr_n, size_t elem_size, comparator_t cmp)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    if (arr_n <= 1)
        return 0;
    for (size_t i = arr_n; i > 1; i--)
    {
        size_t j = 1;
        for (char *pprev = arr, *pcur = pprev + elem_size; j < i; j++, pprev = pcur, pcur += elem_size)
        {
            if (cmp(pprev, pcur) > 0)
                swap(pprev, pcur, elem_size);
        }
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    return calc_elapsed_time(&start, &end);
}

void heapify(void *arr, size_t arr_n, size_t i, size_t elem_size, comparator_t cmp)
{
    size_t largest = i;
    char *plargest = ((char*) arr) + i * elem_size, *pi = plargest, *pl, *pr;   
    // Инициализируем наибольший элемент как корень
    size_t l = 2*i + 1; // левый = 2*i + 1
    size_t r = 2*i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше корня
    if (l < arr_n)
    {
        pl = ((char*) arr) + l * elem_size;
        if (cmp(pl, plargest) > 0)
        {
            largest = l;
            plargest = pl;
        }
    }

   // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < arr_n)
    {
        pr = ((char*) arr) + r * elem_size;
        if (cmp(pr, plargest) > 0)
        {
            largest = r;
            plargest = pr;
        }
    }

    // Если самый большой элемент не корень
    if (largest != i)
    {
        swap(pi, plargest, elem_size);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(arr, arr_n, largest, elem_size, cmp);
    }
}

double heap_sort(void *arr, size_t arr_n, size_t elem_size, comparator_t cmp)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    // Построение кучи (перегруппируем массив)
    for (int i = ((int) arr_n) / 2 - 1; i >= 0; i--)
        heapify(arr, arr_n, (size_t) i, elem_size, cmp);

    // Один за другим извлекаем элементы из кучи
    for (int i = ((int) arr_n) - 1; i >= 0; i--)
    {
        // Перемещаем текущий корень в конец
        swap((char*) arr, ((char*) arr) + i * elem_size, elem_size);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, (size_t) i, 0, elem_size, cmp);
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    return calc_elapsed_time(&start, &end);
}