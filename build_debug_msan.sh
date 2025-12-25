#!/bin/bash
clang -std=gnu99 -g -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -o app.exe ./*.c -lm
