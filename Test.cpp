/*
 * @Author: LetMeFly
 * @Date: 2022-03-21 12:09:53
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-21 12:26:49
 */
#include "LetMeFly.h"

#ifndef Test_CPP
#define Test_CPP
void Test::test_fastRead(bool toFile) {
    if (toFile) {
        freopen("test_fastRead.out", "w", stdout);
    }
    for (int i = 0; i < recordNum; i++) {
        for (set<uint16_t>::iterator it = items[i].begin(); it != items[i].end(); it++) {
            cout << *it << ' ';
        }
        puts("");
    }
    system("pause");
    exit(0);
}
#endif