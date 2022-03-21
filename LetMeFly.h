/*
 * @Author: LetMeFly
 * @Date: 2022-03-16 23:18:30
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-21 14:16:51
 */
#pragma once

#include <iostream>
#include <set>
#include <string>
#define dbg(x) cout << #x << " = " << x << endl
using namespace std;

void inputAnd2minSupportNum();

static class Test{
public:
    void test_fastRead(set<uint16_t> items[], int recordNum, bool toFile = false);
    void test_inputAnd2minSupportNum(int recordNum, bool ifResetRecordnum = false);
} test;
