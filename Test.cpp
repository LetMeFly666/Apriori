/*
 * @Author: LetMeFly
 * @Date: 2022-03-21 12:09:53
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-21 13:27:00
 */
#include "LetMeFly.h"

#ifndef Test_CPP
#define Test_CPP

void Test::test_fastRead(set<uint16_t> items[], int recordNum, bool toFile) {
    puts("items:");
    if (toFile) {
        puts("See it in test_fastRead.out");
        freopen("test_fastRead.out", "w", stdout);
    }
    cout << "Total record num: " << recordNum << endl;
    for (int i = 0; i < recordNum; i++) {
        for (set<uint16_t>::iterator it = items[i].begin(); it != items[i].end(); it++) {
            cout << *it << ' ';
        }
        puts("");
    }
    exit(0);
}

#endif