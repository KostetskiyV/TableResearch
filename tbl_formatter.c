#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tbl_formatter.h"

char *gen_str(size_t len, char ch)
{
    char *space_str = malloc(len);
    for (size_t i = 0; i < len - 1; i++)
        space_str[i] = ch;
    space_str[len - 1] = '\0';
    return space_str;
}

void print_str(const char *str, size_t field_len)
{
    printf("%s", str);
    printf("%s|", gen_str(field_len + 1 - strlen(str), ' '));
}

void print_pos_num(size_t num, size_t field_len)
{
    size_t t = num, num_len = 0, prefix_spaces;
    if (num == 0)
        num_len = 1;
    while (t)
    {
        t /= 10;
        num_len++;
    }
    prefix_spaces = (field_len - num_len) / 2;
    printf("%s%lu%s", gen_str(prefix_spaces + 1, ' '), num, gen_str(field_len - prefix_spaces - num_len + 1, ' '));
}

void print_double(double num, size_t field_len)
{
    size_t num_len = 10, prefix_spaces;
    if (num >= 10)
        num_len = 11;
    else if (num >= 100)
        num_len = 12;
    prefix_spaces = (field_len - num_len) / 2;
    printf("%s%.8f%s", gen_str(prefix_spaces + 1, ' '), num, gen_str(field_len - prefix_spaces - num_len + 1, ' '));
}
