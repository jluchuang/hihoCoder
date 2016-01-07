/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho48.cpp
	Email: jlu_chuang@163.com
	Last modified: 2016-01-06 20:40
*****************************************************/

#include <iostream>
#include <queue>
using namespace std; 

typedef struct adjEdge{
   int no;
   struct adjEdge *next;
   adjEdge(int _no){
       no = _no;
       next = NULL;
   }  
} adj;
typedef adj * pAdj;

pAdj adjTable[100001]; 
int indegree[100001];  
int virus[100001];

void addEdge(int src, int tar) {
    pAdj pNew = new adj(tar);
    pNew->next = adjTable[src]; 
    adjTable[src] = pNew;
    indegree[tar] += 1; 
}

void deleteNode(int no, queue<int> &zeroQ) {
    pAdj pTmp = adjTable[no];
    while(pTmp != NULL) {
        int tar = pTmp->no;

        indegree[tar] -= 1;
        if(indegree[tar] == 0) {
            zeroQ.push(tar);
        }
        virus[tar] += virus[no];
        virus[tar] %= 142857;
 
        pTmp = pTmp->next;
    }
}

int topologicalSorting(int n) {
    queue<int> zeroQ;
    for (int i = 0; i < n; i ++ ) {
        if(indegree[i] == 0) {
            zeroQ.push(i);
        }
    }
    while (!zeroQ.empty()) {
        int cur = zeroQ.front();
        zeroQ.pop();
        deleteNode(cur, zeroQ);
    }
    int sum = 0;
    for(int i = 0; i < n; i ++ ) {
        sum += virus[i];
        sum %= 142857;
    }
    return sum; 
}

int main(){
    int n, m, k; 
    cin>>n>>m>>k;
    for(int i = 0; i < k; i++) {
        int tmp;
        cin>>tmp; 
        virus[tmp-1] = 1;
    }
    
    for(int i = 0; i < m; i++) {
        int a, b;
        cin>>a>>b;
        addEdge(a-1, b-1);
    }
    cout<<topologicalSorting(n)<<endl;
    return 0;
}
