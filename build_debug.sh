#!/bin/bash
gcc -std=gnu99 -g -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -o app.exe ./*.c -lm
