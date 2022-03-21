/*
 * @Author: LetMeFly
 * @Date: 2022-03-16 23:18:30
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-21 13:27:51
 */
#pragma once

#include <iostream>
#include <set>
#define dbg(x) cout << #x << " = " << x << endl
using namespace std;

static class Test{
public:
    void test_fastRead(set<uint16_t> items[], int recordNum, bool toFile = false);
} test;
