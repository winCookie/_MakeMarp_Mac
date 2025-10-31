#include <cctype>
#include <cstdio>
#include <iostream>
using namespace std;

// 快速读取 _int128
void read_fast(__int128 &x) {
    x = 0;
    char c = getchar();
    bool neg = false;

    // 跳过空白字符
    while (isspace(c))
        c = getchar();

    // 处理符号
    if (c == '-') {
        neg = true;
        c = getchar();
    } else if (c == '+') {
        c = getchar();
    }

    // 读取数字
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = getchar();
    }

    if (neg)
        x = -x;
}

// 快速输出 _int128
void print_fast(__int128 x) {
    if (x == 0) {
        putchar('0');
        return;
    }

    if (x < 0) {
        putchar('-');
        x = -x;
    }

    // 使用栈避免反转
    char buffer[40];
    int pos = 0;

    while (x > 0) {
        buffer[pos++] = '0' + (x % 10);
        x /= 10;
    }

    while (pos > 0) {
        putchar(buffer[--pos]);
    }
}

int main() {
    __int128 a;
    read_fast(a);
    print_fast(a);
}