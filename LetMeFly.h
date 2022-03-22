/*
 * @Author: LetMeFly
 * @Date: 2022-03-16 23:18:30
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-22 16:46:19
 */
#pragma once

#include <unordered_set>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#define dbg(x) cout << #x << " = " << x << endl
using namespace std;

#define MAX_RECORD_NUM 88162 + 1
#define MAX_ITEMID_NUM 16470 + 1

typedef unordered_set<uint16_t> set_u16;

void inputAnd2minSupportNum();

static class Test{
public:
    void test_fastRead(set_u16 items[], int recordNum, bool toFile = false);
    void test_inputAnd2minSupportNum(int recordNum, bool ifResetRecordnum = false);
} test;
