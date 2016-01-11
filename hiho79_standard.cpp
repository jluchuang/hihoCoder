/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho79_standard.cpp
	Email: jlu_chuang@163.com
	Last modified: 2016-01-11 10:44
*****************************************************/
#include<algorithm>
#include<bitset>
#include<cassert>
#include<cctype>
#include<cfloat>
#include<climits>
#include<cmath>
#include<complex>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<deque>
#include<iostream>
#include<list>
#include<map>
#include<numeric>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define MAXN 20005 
#define MAXM 800005 
using namespace std; 
struct node 
{ 
    int x,y,next; 
}edge[MAXM]; 
int _next[MAXN],En,dfn[MAXN],low[MAXN],tp[MAXN],tpnum,DfsIndex; 
bool instack[MAXN]; 
stack<int> mystack; 
void addedge(int x,int y) 
{ 
    edge[++En].next=_next[x],_next[x]=En; 
    edge[En].x=x,edge[En].y=y; 
} 
void InputData(int n,int m) 
{ 
    int x,y,s,x0,x1,y0,y1; 
    memset(_next,0,sizeof(_next)),En=0; 
    while (m--) 
    { 
        scanf("%d%d%d",&x,&y,&s); 
        x0=x<<1,x1=x0|1,y0=y<<1,y1=y0|1; 
        if (!s) 
        { 
            addedge(x0,y1),addedge(y0,x1); 
        }else 
        { 
            addedge(x1,y0),addedge(y1,x0); 
        } 
    } 
    return; 
} 
void tarjan(int x) 
{ 
    int y,k; 
    dfn[x]=low[x]=++DfsIndex; 
    instack[x]=true; 
    mystack.push(x); 
    for (k=_next[x];k;k=edge[k].next) 
    { 
        y=edge[k].y; 
        if (!dfn[y]) 
        { 
            tarjan(y); 
            low[x]=min(low[x],low[y]); 
        }else 
            if (instack[y]) 
                low[x]=min(low[x],dfn[y]); 
    } 
    if (low[x]==dfn[x]) 
    { 
        tpnum++; 
        do 
        { 
            x=mystack.top(); 
            mystack.pop(); 
            tp[x]=tpnum; 
            instack[x]=false; 
        }while (low[x]!=dfn[x]); 
    } 
    return; 
} 
bool judge(int n) 
{ 
    int i; 
    for (i=0;i<n;i++) 
        if (tp[i<<1]==tp[i<<1|1]) return false; 
        return true; 
} 
int main() 
{ 
    int cases,n,m; 
    scanf("%d",&cases); 
    while (cases--) 
    { 
        scanf("%d%d",&n,&m); 
        InputData(n,m); 
        memset(dfn,0,sizeof(dfn)); 
        memset(instack,false,sizeof(instack)); 
        while (!mystack.empty()) mystack.pop(); 
        DfsIndex=tpnum=0; 
        for (int i=0;i<(n<<1);i++) 
            if (!dfn[i]) tarjan(i); 
            if (judge(n)) puts("Yes"); 
            else puts("No"); 
    } 
    return 0; 
}

