/*
 * @Author: LetMeFly
 * @Date: 2022-03-16 23:18:30
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-21 12:28:36
 */
#pragma once

#include <iostream>
#include <set>
#define dbg(x) cout << #x << " = " << x << endl
using namespace std;


static set<uint16_t> items[88163];  // 方法四、交易记录
static int recordNum = 0;  // 第recordNum条交易记录

static class Test{
public:
    void test_fastRead(bool toFile = false);
} test;
