/*
 * @Author: LetMeFly
 * @Date: 2022-03-16 23:18:11
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-23 08:41:51
 */
#include "LetMeFly.h"

int countItemNum() {
    unordered_set<int> se;
    freopen("Source/retail.dat", "r", stdin);
    int t;
    int cnt = 0;
    while (~scanf("%d", &t)) {
        se.insert(t);
        if (t < 0 || t >= 16470)
            cout << t << endl;
        cnt++;
    }
    dbg(cnt);
    return se.size();
}