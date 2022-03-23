/*
 * @Author: LetMeFly
 * @Date: 2022-03-16 23:20:32
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-23 08:43:10
 */
// g++ main.cpp Test.cpp -o main.exe

#include "LetMeFly.h"
#define DATA_NAME "Source\\retail.dat"

set_u16 items[MAX_RECORD_NUM];  // 方法四、交易记录
int recordNum = 0;  // 第recordNum条交易记录
int minSupportNum;  // 最少出现多少次才能
typedef pair<vector<uint16_t>, int> Log;  // <[id1, id2, id3, ...], 出现次数>
map<vector<uint16_t>, int> ma[MAX_RECORD_NUM];  // ma[i]：商品个数为i的 <[id1, id2, ..., idi], 出现次数>
int maxItemNumPerLog = 1;  // 每项的商品数量
int timesEachItemOccured[MAX_ITEMID_NUM];  // 每个商品出现的次数，用于预处理L1

/* 读入数据 */
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
                timesEachItemOccured[num]++;
            }
            if (c == '\n') {
                recordNum++;
            }
            lastIsNum = false;
        }
    }
    if (lastIsNum) {  // 文件最后一个是数字
        items[recordNum].insert(num);
        timesEachItemOccured[num]++;
    }
    if (c != '\n') {  // 如果文件不是以回车结尾的，那么recordNum要+1
        recordNum++;
    }
    fclose(fp);
}

/* 输入最小支持度并转换为最小支持数 */
void inputAnd2minSupportNum() {
    string s;
    cin >> s;
    if (s[s.size() - 1] == '%') {
        double integer = 0;
        double decimal = 0;
        double decimalRate = 1;
        for (int i = 0; i < s.size() - 1; i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                if (decimalRate == 1) {
                    integer *= 10;
                    integer += s[i] - '0';
                }
                else {
                    decimal += (s[i] - '0') * decimalRate;
                    decimalRate /= 10;
                }
            }
            else {
                if (s[i] != '.') {
                    throw("Input Error, include wrongful character.");
                }
                if (decimalRate != 1) {
                    throw("Input Error, include not only one dot.");
                }
                decimalRate /= 10;
            }
        }
        double percent = integer + decimal;
        minSupportNum = percent * recordNum / 100;
        if ((double)minSupportNum * 100 /  recordNum < percent)
            minSupportNum++;
    }
    else {
        minSupportNum = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                minSupportNum *= 10;
                minSupportNum += s[i] - '0';
            }
            else {
                throw("Input Error, include wrongful character.");
            }
        }
    }
    printf("recordNum = %d, minSupportNum = %d, minSupport = %lf%%\n", recordNum, minSupportNum, (double)minSupportNum * 100 / recordNum);
}

void calu() {
    // init L1
    for (uint16_t i = 0; i < MAX_ITEMID_NUM; i++) {
        if (timesEachItemOccured[i] >= minSupportNum) {
            ma[maxItemNumPerLog][{(uint16_t)i}] = timesEachItemOccured[i];
        }
    }
    /* 判断a和b的前sameNum个元素是否相同 */
    auto ifSame = [](const vector<uint16_t> &a, const vector<uint16_t> &b, int sameNum) {
        for (int i = 0; i < sameNum; i++)
            if (a[i] != b[i])
                return false;
        return true;
    };
    /**判断一个vector是否满足最小支持度
     * 如果满足就返回它的出现次数
     * 如果不满足就返回-1
     */
    auto ifOkV = [](vector<uint16_t> &v) {
        int num = v.size();
        // num - 1项是否都满足
        for (int i = 0; i < num; i++) {
            vector<uint16_t> temp = v;
            temp.erase(temp.begin() + i);
            if (!ma[num - 1].count(temp)) {
                return -1;
            }
        }
        // v出现的次数
        int occurTime = 0;
        for (int i = 0; i < recordNum; i++) {
            bool allExists = true;
            for (uint16_t &t : v) {
                if (!items[i].count(t)) {
                    allExists = false;
                    break;
                }
            }
            occurTime += allExists;
        }
        return occurTime >= minSupportNum ? occurTime : -1;
    };
    auto addLR = [ifOkV](map<vector<uint16_t>, int>::iterator ita, map<vector<uint16_t>, int>::iterator itb) {
        int num = ita->first.size();
        for (map<vector<uint16_t>, int>::iterator i = ita; i != itb; i++) {
            map<vector<uint16_t>, int>::iterator j = i;
            for (j++; j != itb; j++) {
                vector<uint16_t> v = i->first;
                v.push_back(j->first[num - 1]);
                int occurTimes = ifOkV(v);
                if (occurTimes != -1) {
                    ma[num + 1][v] = occurTimes;
                }
            }
        }
    };
    while (ma[maxItemNumPerLog].size()) {
        maxItemNumPerLog++;
        /**找到所有前(maxItemNumPerLog - 2)个item相同的 l和r
         * 也就是说把[0, ma[maxItemNumPerLog - 1].size()) 分成 [l1, r1) + [l2, r2) + ... + [ln, rn)
         * 其中r1 = l2, r2 = l3, ..., rn-1 = ln; rn = maxItemNumPerLog - 1
         * 并且：
         *     对∀i∈[1, n]，对∀j, k∈[li, ri)，对∀m∈[0, maxItemNumPerLog - 2)，有ma[maxItemNumPerLog - 1]->(j-th vector)->(m-th item) = ma[maxItemNumPerLog - 1]->(k-th vector)->(m-th item)
         *     对∀i, j∈[1, n]且i ≠ j，对∀ki∈[li, ri), kj∈[lj, rj)，∃m∈[0, maxItemNumPerLog - 2)，使ma[maxItemNumPerLog - 1]->(ki-th vector)->(m-th item) ≠ ma[maxItemNumPerLog - 1]->(kj-th vector)->(m-th item)
         */
        map<vector<uint16_t>, int>::iterator lastIter = ma[maxItemNumPerLog - 1].begin();
        for (map<vector<uint16_t>, int>::iterator it = ++ma[maxItemNumPerLog - 1].begin(); it != ma[maxItemNumPerLog - 1].end(); it++) {
            if (ifSame(lastIter->first, it->first, maxItemNumPerLog - 2)) {
                addLR(lastIter, it);
            }
        }

    }
    maxItemNumPerLog--;  // 因为最后一次ma为空
}

void prt() {
    printf("All founded. MaxItemNum = %d\n", maxItemNumPerLog);
    for (int i = 1; i <= maxItemNumPerLog; i++) {
        printf("\n");
        printf("itemNum: %d, logNum: %d\n", i, (int)ma[i].size());
        printf("-------------\n");
        for (map<vector<uint16_t>, int>::iterator it = ma[i].begin(); it != ma[i].end(); it++) {
            bool firstPrt = true;
            putchar('[');
            for (const uint16_t &t : it->first) {
                if (firstPrt)
                    firstPrt = false;
                else
                    printf(", ");
                printf("%d", t);
            }
            putchar(']');
            printf(" -> %d\n", it->second);
        }
    }
}

int main() {
    printf("Please input the min_support, 80.756%% for percent, 80756 for num:");
    fastRead();
    inputAnd2minSupportNum();
    time_t begin = clock();
    calu();
    time_t end = clock();
    prt();
    cout << "Calculate cost time: " << ((double)(end - begin)) / CLK_TCK << "s" << endl;
    return 0;
}