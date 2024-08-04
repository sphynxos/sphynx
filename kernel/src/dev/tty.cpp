/*
Sphynx Operating System

File: tty.cpp
Author: Kevin Alavik
Year: 2024

License: MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Description: Implementation of the Sphynx TTY system
*/

#include <dev/tty.hpp>
#include <common.hpp>
#include <stdlib/string.hpp>

void _putc(char ch) {
    flanterm_write(ftCtx, &ch, sizeof(ch));
}

void write_number(int num) {
    char buffer[12];
    int i = 0;
    bool is_negative = num < 0;
    if (is_negative) {
        num = -num;
    }
    do {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    } while (num > 0);
    if (is_negative) {
        buffer[i++] = '-';
    }
    while (i > 0) {
        _putc(buffer[--i]);
    }
}

template <>
void tty_write<char>(char ch) {
    _putc(ch);
}

template <>
void tty_write<const char*>(const char* str) {
    while (*str) {
        _putc(*str++);
    }
}

template <>
void tty_write<char*>(char* str) {
    while (*str) {
        _putc(*str++);
    }
}

template <>
void tty_write<int>(int num) {
    write_number(num);
}

template <>
void tty_write<unsigned int>(unsigned int num) {
    write_number(num);
}