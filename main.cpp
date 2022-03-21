/*
 * @Author: LetMeFly
 * @Date: 2022-03-16 23:20:32
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-21 12:29:09
 */
// g++ main.cpp CountItemNum.cpp -o main.exe

#include "LetMeFly.h"
#define DATA_NAME "Source/retail.dat"

void fastRead() {
    
    char c;
    bool lastIsNum = false;
    uint16_t num;
    FILE* fp = fopen(DATA_NAME, "r");
    while (~(c = fgetc(fp))) {
        if (c >= '0' && c <= '9') {
            if (lastIsNum) {  // 继续数字
                num *= 10;
                num += c - '0';
            }
            else {  // 非数字->数字
                num = c - '0';
            }
            lastIsNum = true;
        }
        else {
            if (lastIsNum) {  // 数字->非数字
                items[recordNum].insert(num);
            }
            if (c == '\n') {
                recordNum++;
            }
            lastIsNum = false;
        }
    }
    if (lastIsNum) {  // 文件最后一个是数字
        items[recordNum].insert(num);
    }
}

int main() {
    fastRead();
    test.test_fastRead();
    system("pause");
    return 0;
}