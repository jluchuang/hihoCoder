/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: tarjan.cpp
	Email: jlu_chuang@163.com
	Last modified: 2016-01-07 16:42
*****************************************************/
#include <iostream> 
#include <stack>
#include <vector>
using namespace std;

typedef struct AdjEdge {
    int tar;     // Target Node
    struct AdjEdge * next; 
    AdjEdge(int _tar) {
        tar = _tar; 
        next = NULL; 
    } 
} Edge; 

typedef Edge * PEdge; 

int curIndex; 

void tarjan(int v, PEdge *adjTable, stack<int> &dfsS, 
         vector<int> &index, vector<int> &lowIndex, 
         vector<int> &visited, vector<int> &inStack, vector< vector<int> > &res);

int min(int a, int b ){
    if(a > b) {
        return b; 
    }
    return a;
}

void addEdge(int src, int tar, PEdge *adjTable) {
    PEdge pEdge = new Edge(tar); 
    pEdge->next = adjTable[src];
    adjTable[src] = pEdge; 
}

vector< vector<int> > tarjan(int n, PEdge *adjTable){
    stack<int> dfsS;
    vector<int> visited(n, 0); 
    vector<int> inStack(n, 0);
    vector<int> index(n, 0); 
    vector<int> lowIndex(n, 0);
    vector< vector<int> > res;
    
    curIndex = 1; 
    for(int i = 0; i < n; i ++) {
        if(visited[i] == 0) {
            tarjan(i, adjTable, dfsS, index, lowIndex, visited, inStack, res); 
        }
    }
    return res;
}


void tarjan(int v, PEdge *adjTable, stack<int> &dfsS, 
         vector<int> &index, vector<int> &lowIndex, 
         vector<int> &visited, vector<int> &inStack, vector< vector<int> > &res) {
    index[v] = lowIndex[v] = curIndex;
    curIndex ++;
    visited[v] = 1;
    inStack[v] = 1; 
    dfsS.push(v);
    
    // cout<<"here"<<v<<endl;
     
    PEdge pTmp = adjTable[v]; 
    while(pTmp != NULL) {
        int tar = pTmp->tar;
        if(visited[tar] == 0) {
             tarjan(tar, adjTable, dfsS, index, lowIndex, visited, inStack, res);
             lowIndex[v] = min(lowIndex[v], lowIndex[tar]);  
        }
        else {
             if(inStack[tar] == 1) {
                 lowIndex[v] = min(lowIndex[v], lowIndex[tar]); 
             }
        }
        pTmp = pTmp->next; 
    } 
    
    if(lowIndex[v] == index[v]) {
        vector<int> component; 
        while(v != dfsS.top()) {
            component.push_back(dfsS.top());
            dfsS.pop();
        }
        dfsS.pop();
        component.push_back(v); 
        res.push_back(component);
    }
}

int main(){
    int n = 0;   // n nodes
    int m = 0;   // m edges
    cin>>n>>m;
    
    // Adjcent table 
    PEdge * adjTable = new PEdge[n];
    
    for (int i = 0; i < m; i ++ ) {
        int src = 0; 
        int tar = 0;
        cin>>src>>tar;
        addEdge(src-1, tar-1, adjTable); 
    }  
    
    vector< vector<int> > res = tarjan(n, adjTable); 
    
    for(vector< vector<int> >::iterator it = res.begin(); it != res.end(); it ++) {
        vector<int> comp = *it; 
        cout<<"{";
        for(vector<int>::iterator comIt = comp.begin(); comIt != comp.end(); comIt ++){
            cout<<' '<< *comIt;
        }
        cout<<" }"<<endl; 
    }
    return 0; 
}



