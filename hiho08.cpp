/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho08.cpp
	Email: jlu_chuang@163.com
	Last modified: 2015-12-21 16:51
*****************************************************/

#include "iostream"
#include "algorithm"
#include "cstdio"
#include "cstring"
#include "set"
#include "vector"
using namespace std;

int dp[2][1<<10];
int cnt[1<<10];
int num[1010];
int N,M,Q;

int reans(int pos,int flag){
    int v = pos>>1;
    if(cnt[v]<Q)
        return max(dp[flag][v+(1<<(M-1))],dp[flag][v]);
    if(cnt[v]==Q)
        return dp[flag][v];
}

int recnt(int x){
    int cntx=0;
    while(x){
        if(x&1)cntx+=1;
        x>>=1;
    }
    return cntx;
}
int main()
{
    cin>>N>>M>>Q;
    int flag =0;
    memset(dp,0,sizeof(dp));
    int len = 1<<M;
    for(int i=0;i<len;i++){
        cnt[i]=recnt(i);
    }
    for(int i=1;i<=N;i++){
        cin>>num[i];
        for(int j=0;j<len;j+=2){
            if(cnt[j]>Q){
                dp[flag][j]=dp[flag][j+1]=0;
                continue;
            }
            if(cnt[j]==Q){
                dp[flag][j]=reans(j,flag^1);
                dp[flag][j+1]=0;
                continue;
            }
            dp[flag][j]=dp[flag][j+1]=reans(j,flag^1);
            dp[flag][j+1]+=num[i];
        }
        flag^=1;
    }
    int ans=0;
    for(int i=0;i<len;i++)ans=max(dp[flag^1][i],ans);
    printf("%d\n",ans);
    return 0;
}
