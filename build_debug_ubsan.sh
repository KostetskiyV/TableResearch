#!/bin/bash
clang -std=gnu99 -g -Wall -Werror -Wpedantic -Wextra -fsanitize=undefined -fno-omit-frame-pointer -Wfloat-equal -Wfloat-conversion -o app.exe ./*.c -lm
