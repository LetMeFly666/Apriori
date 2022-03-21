/*
 * @Author: LetMeFly
 * @Date: 2022-03-21 12:09:53
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-21 14:29:36
 */
#include "LetMeFly.h"

#ifndef Test_CPP
#define Test_CPP

/* main.cpp: test.test_fastRead(items, recordNum); */
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

/**测试最小支持数的输入与计算
 * 如果ifRestRecordnum为真，那么将舍弃recordNum而转为让测试者输入recordNum
 * main: test.test_inputAnd2minSupportNum(recordNum);
 * warning: 请勿令ifResetRecordnum为真，即使这样inputAnd2minSupportNum()中的recordNum也不会改变
*/
void Test::test_inputAnd2minSupportNum(int recordNum, bool ifResetRecordnum) {
    extern int minSupportNum;
    while (true) {
        if (ifResetRecordnum) {
            cin >> recordNum;
        }
        inputAnd2minSupportNum();
        printf("recordNum = %d, minSupportNum = %d, minSupport = %lf%%\n", recordNum, minSupportNum, (double)minSupportNum * 100 / recordNum);
        printf("minSupportNum - 1 = %d, minSupport_1 = %lf%%\n", minSupportNum - 1, double(minSupportNum - 1) * 100 / recordNum);
    }
    exit(0);
}

#endif