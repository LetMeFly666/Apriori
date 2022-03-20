/*
 * @Author: LetMeFly
 * @Date: 2022-03-20 10:16:13
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-20 12:46:32
 */
#include <bits/stdc++.h>
using namespace std;
#define mem(a) memset(a, 0, sizeof(a))
#define dbg(x) cout << #x << " = " << x << endl
#define fi(i, l, r) for (int i = l; i < r; i++)
#define cd(a) scanf("%d", &a)
typedef long long ll;

struct Trie {
    Trie *childs[26];
    Trie *fail, *father;
    uint8_t thisChar;
    vector<int> wordLength;  // 以此为结尾的单词的长度
    Trie() {
        fail = father = nullptr;
        for (int i = 0; i < 26; i++) {
            childs[i] = nullptr;
        }
    }
};

Trie *build(vector<string> &words) {
    Trie *root = new Trie;
    // region 插入单词，构建Trie树
    for (string &word : words) {
        Trie *t = root;
        for (char &c : word) {
            if (!t->childs[c - 'a']) {
                t->childs[c - 'a'] = new Trie;
                t->childs[c - 'a']->father = t;
                t->childs[c - 'a']->thisChar = c - 'a';
            }
            t = t->childs[c - 'a'];
        }
        t->wordLength.push_back(word.size());
    }
    // endregion 插入单词，构建Trie树
    // region 构建fail指针
    queue<Trie *> q;
    root->fail = root;
    for (int i = 0; i < 26; i++) {  // root和第1层的father指针特殊处理
        if (root->childs[i]) {
            root->childs[i]->fail = root;
            for (int j = 0; j < 26; j++) {
                if (root->childs[i]->childs[j]) {
                    q.push(root->childs[i]->childs[j]);
                }
            }
        }
    }
    while (q.size()) {
        Trie *t = q.front();
        q.pop();
        if (t->father->fail->childs[t->thisChar]) {  // father的fail指针指向的节点有这个字符的儿子
            t->fail = t->father->fail->childs[t->thisChar];
            for (int &wordLength : t->father->wordLength) {  // 
                t->wordLength.push_back(wordLength);
            }
        }
        else {
            t->fail = root;
        }
        for (int i = 0; i < 26; i++) {
            if (t->childs[i]) {
                q.push(t->childs[i]);
            }
        }
    }
    // endregion 构建fail指针
    return root;
}

void destroy(Trie *root) {
    for (int i = 0; i < 26; i++) {
        if (root->childs[i]) {
            destroy(root->childs[i]);
        }
    }
    delete root;
}

vector<string> &read() {
    int n;
    cin >> n;
    // if (n == 1) {
    //     puts("1");  // 这里是想debug一下测试数据2
    //     exit(0);
    // }
    static vector<string> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}

int count(Trie *root, string &s) {
    int ans = 0;
    Trie *t = root;
    for (char &c : s) {
        // if (!t) {
        //     puts("***");
        //     exit(0);
        // }
        if (t->childs[c - 'a']) {
            t = t->childs[c - 'a'];
            ans += t->wordLength.size();
        }
        else {
            t = t->fail;
        }
    }
    return ans;
}

int main() {
    freopen("P3808_2.in", "r", stdin);  //*****
    vector<string> words = read();
    Trie *root = build(words);
    string t;
    cin >> t;
    cout << count(root, t) << endl;
    destroy(root);
    return 0;
}