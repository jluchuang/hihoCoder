/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho53.cpp
	Email: jlu_chuang@163.com
	Last modified: 2016-01-11 21:26
*****************************************************/
#include <iostream>
#include <stack>
#include <vector>  
using namespace std;

typedef struct adjEdge { 
    int tar; 
    struct adjEdge *next;
    adjEdge(int _tar) {  
        tar = _tar;
        next = NULL; 
    } 
} Edge; 

typedef Edge * PEdge;

PEdge *adj = NULL; 
int n = 0;
int componentsNo = 1; 
int curIndex = 0;
stack<int> S;  

void addEdge(int src, int tar) {
    PEdge ptmp = new Edge(tar); 
    ptmp->next = adj[src]; 
    adj[src] = ptmp; 
}

void tarjan(int v, vector<int> &index, vector<int> &lowIndex, vector<int> &isInStack, vector<int> &res) {
    index[v] = lowIndex[v] = ++curIndex; 
    isInstack[v] = 1;
    S.push(v); 
    
    for(PEdge p = adj[v]; p; p = p->next ) {
        int tar = p->tar; 
        if(index[tar] == -1) {
            tarjan(tar, index, lowIndex, )
        }
    }
}

int main() {
    
    return 0; 
}
