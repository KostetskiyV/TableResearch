#!/bin/bash
gcc -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -o app.exe ./*.c -lm
