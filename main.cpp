/*
 * @Author: LetMeFly
 * @Date: 2022-03-16 23:20:32
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-22 09:02:00
 */
// g++ main.cpp Test.cpp -o main.exe

#include "LetMeFly.h"
#define DATA_NAME "Source\\retail.dat"

set<uint16_t> items[MAX_RECORD_NUM];  // 方法四、交易记录
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
    for (uint16_t i = 0; i < MAX_ITEMID_NUM; i++) {
        if (timesEachItemOccured[i] >= minSupportNum) {
            ma[maxItemNumPerLog][{(uint16_t)i}] = timesEachItemOccured[i];
        }
    }
    while (ma[maxItemNumPerLog].size()) {
        maxItemNumPerLog++;
        
    }
    maxItemNumPerLog--;  // 因为最后一次ma为空
}

void prt() {
    for (int i = 1; i <= maxItemNumPerLog; i++) {
        printf("\n");
        printf("itemNum: %d, logNum: %lld\n", i, ma[i].size());
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
    calu();
    prt();
    return 0;
}