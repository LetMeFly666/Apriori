<!--
 * @Author: LetMeFly
 * @Date: 2022-03-16 22:50:20
 * @LastEditors: LetMeFly
 * @LastEditTime: 2022-03-16 23:16:52
-->
# Apriori算法实现关联规则的数据挖掘

## 前言

<a href="https://github.com/LetMeFly666/Apriori">这个项目</a>正在完成中，目前是Private状态，预计今年(2022)5月份开源(变成public)

现在项目为私有的原因主要有两个：
+ 一是项目还未完工
+ 二是这个作业吧，怎么说，挺怕检查的时候被查重的

## 实现目标

目标只有一个，就是对于一个给定的置信度，用**尽可能少的时间**求出<code>Source/retail.dat</code>的所有关联规则

也就是说，此算法将会尽可能多地采用空间换时间、多线程等方法，在8G内存、i5处理器的电脑上计算出结果。


