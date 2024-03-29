<!--
 * @Author: LetMeFly
 * @Date: 2022-03-16 22:50:20
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-04-16 19:54:07
-->
# Apriori算法实现关联规则的数据挖掘

## 前言

Apriori算法实现关联规则的数据挖掘

+ 在线文档 [https://apriori.letmefly.xyz](https://apriori.letmefly.xyz)

+ 项目地址 [https://github.com/LetMeFly666/apriori](https://github.com/LetMeFly666/apriori)

+ See [FP-growth(https://github.com/LetMeFly666/FP-growth)](https://github.com/LetMeFly666/FP-growth) For More


## 实现目标

目标只有一个，就是对于一个给定的置信度，用**尽可能少的时间**求出<code>Source/retail.dat</code>的所有关联规则

也就是说，此算法将会尽可能多地采用空间换时间、多线程等方法，在8G内存、i5处理器的电脑上计算出结果。

### 数据分析

这个数据共有<code>88162</code>行(消费记录)，总共有<code>16470</code>种产品。

#### 数据存储方式

##### 方法一

每条消费记录存入一个vector中，```vector<uint16_t> items[88162]```

每个vector中记录都有哪些商品。

###### 存储方式示例

Data:

```
1 2 5
3 4 5
4
```

Storage:

```cpp
vector<uint16_t> itmes[3] = {
    {1, 2, 5},
    {3, 4, 5},
    {4}
};
```

###### 空间使用

有多少数据大约就会使用多少空间(不是很清楚vector具体是怎么动态扩容的)

经过统计共有908576个数据，需要约1e6*2Byte≈2M的内存空间

##### 方法二

每件商品存入一个vector中，```vector<int> itmes```<small>(2^16=65536<88162，不可用uint16_t，这里先不考虑数据压缩)</small>

每个vector记录这个商品出现在哪些消费记录中。

###### 存储方式示例

Data:

```
1 2 5
3 4 5
4
```

Storage:

```cpp
vector<int> itmes[5] = {
    {0},
    {0},
    {1},
    {1, 2},
    {0, 1}
};
```

###### 空间使用

类似方法一，共需要约1e6*4Byte≈4M的内存空间


##### 方法三

类似方法二，每件商品用一个bitset来存储。```bitset<908576> items[16470]```

bitset的第i位代表这件商品是否出现在第i条消费记录中。

###### 存储方式示例

Data:

```
1 2 5
3 4 5
4
```

Storage:

```cpp
bitset<3> items[5] = {
    0b001,
    0b001,
    0b010,
    0b110,
    0b011
};
```

###### 空间使用

共有16470种商品，共有908576条记录，因此共需要空间16470*908576bit=1870530840Byte=1783.87722015380859375M=1.742067597806453704833984375G≈1.75G的内存空间。


##### 方法四

<del>每条消费记录建立一个Trie树，树上插入这个消费记录的每个商品。</del>每条消费记录建立一个<del>set</del>unordered_set```unordered_set<uint16_t> items[88162]```，这样查询一个商品是否在某个记录中就比较快。

###### 存储方式示例

不便展示

###### 空间使用

空间复杂度O(∑商品数)，只是常数比较大

### 算法原理

Ln是所有的 商品个数为n的、支持度≥给定支持度的商品集 的集合

对于一个确定的n，要判同时包含某n件商品的消费记录的条数，以此来确定是否能够满足给定支持度。

Ln是由Ln-1得到的。假设n=3，ab、ac∈Ln-1，由Ln-1得到Ln的时候，由ab和ac就可以组成abc(长度为3)。

如果bc∉Ln-1，那么就直接排除abc。（其中bc是abc的一个长度为n-1的子集。这么剪枝要找到所有abc中长度为2的子集，复杂度为O(n)）

#### 主要瓶颈

1. 统计abc的出现次数

2. 找C中前缀全部相同的项（abc + abd -> abcd）


## 后记

算法已经实现，暂未优化。主要就是L1->L2比较慢。假如使用数据<code>Source\retail.dat</code>且令最小支持度为2%，那么L1就有20个元素。

一共88162条记录，88162*(20*19/2)=16,750,780，set.count再加个log(N)，应该是执行了最少1e8的运算。

| 支持度 | 耗时 | 结果 |
| :--: | :--: | :--: |
| 5% | 0.333s | 20 + 22 + 12 + 1 = 55 |
| 1% | 35.729s | 70 + 58 + 25 + 6 = 159 |
| 0.8% | 75.483s | 101 + 98 + 38 + 6 = 243 |
| 0.5% | 360.879s | 221 + 237 + 102 + 19 + 1 = 580 |

## 不同的方法实现

| 描述                                             | 方案一 | 方案二          |
| ------------------------------------------------ | ------ | --------------- |
| 方案四中，每条消费记录用set还是unordered_set来存 | set ❌  | unordered_set ✔ |


## Release

<details>
<summary>v0.0.1-Bugx86版</summary>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.1/Apriori-v0.0.1-x64-Debug.exe">Apriori-v0.0.1-x64-Debug.exe</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.1/Apriori-v0.0.1-x64-Release.exe">Apriori-v0.0.1-x64-Release.exe</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.1/Apriori-v0.0.1-x86-Debug.exe">Apriori-v0.0.1-x86-Debug.exe</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.1/Apriori-v0.0.1-x86-Release.exe">Apriori-v0.0.1-x86-Release.exe</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.1/Apriori-v0.0.1-Codes.rar">Apriori-v0.0.1-Codes.rar</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.1/Apriori-v0.0.1-Codes.zip">Apriori-v0.0.1-Codes.zip</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/archive/refs/tags/v0.0.1.zip">Source code (zip)</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/archive/refs/tags/v0.0.1.tar.gz">Source code (tar.gz)</a></li>
</details>

<details>
<summary>v0.0.2-Bugx86版</summary>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.2/Apriori-v0.0.2-x64-Debug.exe">Apriori-v0.0.2-x64-Debug.exe</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.2/Apriori-v0.0.2-x64-Release.exe">Apriori-v0.0.2-x64-Release.exe</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.2/Apriori-v0.0.2-x86-Debug.exe">Apriori-v0.0.2-x86-Debug.exe</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.2/Apriori-v0.0.2-x86-Release.exe">Apriori-v0.0.2-x86-Release.exe</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.2/Apriori-v0.0.2-Codes.rar">Apriori-v0.0.2-Codes.rar</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.0.2/Apriori-v0.0.2-Codes.zip">Apriori-v0.0.2-Codes.zip</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/archive/refs/tags/v0.0.2.zip">Source code (zip)</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/archive/refs/tags/v0.0.2.tar.gz">Source code (tar.gz)</a></li>
</details>

<details>
<summary>v0.1.0</summary>
<li><a href="https://github.com/LetMeFly666/Apriori/releases/download/v0.1.0/Apriori-v0.1.0-x64-Release.exe">Apriori-v0.1.0-x64-Release.exe</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/archive/refs/tags/v0.1.0.zip">Source code (zip)</a></li>
<li><a href="https://github.com/LetMeFly666/Apriori/archive/refs/tags/v0.1.0.tar.gz">Source code (tar.gz)</a></li>
</details>
