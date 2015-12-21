#! /usr/bin/python 

import sys
import math

dp = [[0 for i in range(1<<10)] for j in range(2)]
cnt = [0 for i in range(1<<10)]
n = 0
m = 0
q = 0

def cal_ans(pos, flag):
    v = pos >> 1
    if cnt[v] < q:
        return max(dp[flag][v+(1<<(m-1))], dp[flag][v])
    if cnt[v] == q:
        return dp[flag][v]

def cal_cnt(x):
    cntx = 0
    while(x != 0): 
        if (x&1 == 1): 
            cntx += 1
	x = x>>1
    return cntx

if __name__=="__main__":
    n,m,q = map(int, raw_input().split())
    
    len = 1 << m
    for i in range(0, len): 
        cnt[i] = cal_cnt(i)
    #print cnt

    num=map(int, raw_input().split())
    #print num
    
    flag = 0
    for i in range(1, n+1):
        for j in range(0, len, 2): 
            if cnt[j] > q :
                dp[flag][j] = dp[flag][j+1] = 0
                continue
            if cnt[j] == q : 
                dp[flag][j] = cal_ans(j, flag^1)
                dp[flag][j+1] = 0 
                continue
            dp[flag][j] = dp[flag][j+1] = cal_ans(j, flag^1)
            dp[flag][j+1] += num[i-1]
        flag ^= 1
    #print dp 
    ans = 0
    for i in range(0, len) :
        ans = max(dp[flag^1][i],ans) 
    print ans
