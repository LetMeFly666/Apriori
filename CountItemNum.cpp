/*
 * @Author: LetMeFly
 * @Date: 2022-03-16 23:18:11
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-18 11:03:28
 */
#include "LetMeFly.h"

int countItemNum() {
    set<int> se;
    freopen("Source/retail.dat", "r", stdin);
    int t;
    while (~scanf("%d", &t)) {
        se.insert(t);
        if (t < 0 || t >= 16470)
            cout << t << endl;
    }
    return se.size();
}