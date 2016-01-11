/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho54.cpp
	Email: jlu_chuang@163.com
	Last modified: 2016-01-07 15:22
*****************************************************/
#include <iostream>
#include <stack>
#include <vector> 
using namespace std; 

typedef struct AdjEdge {
    int tar; // Target Node
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
         vector<int> &visited, vector<int> &inStack, 
         vector< vector<int> > &res, vector<int> &newIndex);

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

vector< vector<int> > tarjan(int n, PEdge *adjTable, vector<int> &newIndex){
    stack<int> dfsS;
    vector<int> visited(n, 0); 
    vector<int> inStack(n, 0);
    vector<int> index(n, 0); 
    vector<int> lowIndex(n, 0);
    vector< vector<int> > res;
    
    curIndex = 1; 
    for(int i = 0; i < n; i ++) {
        if(visited[i] == 0) {
            tarjan(i, adjTable, dfsS, index, lowIndex, visited, inStack, res, newIndex); 
        }
    }
    return res;
}


void tarjan(int v, PEdge *adjTable, stack<int> &dfsS, 
         vector<int> &index, vector<int> &lowIndex, 
         vector<int> &visited, vector<int> &inStack, 
         vector< vector<int> > &res, vector<int> &newIndex) {
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
             tarjan(tar, adjTable, dfsS, index, lowIndex, visited, inStack, res, newIndex);
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
            int cur = dfsS.top();
            component.push_back(cur);
            newIndex[cur] = res.size();
            dfsS.pop();
            inStack[cur] = 0; 
        }
        dfsS.pop();
        inStack[v] = 0; 
        component.push_back(v); 
        newIndex[v] = res.size();
        res.push_back(component);
    }
}

void addEdgeToNewTable(int src, int tar, PEdge *newAdj){
    PEdge pTmp = newAdj[src];
    bool flag = true;  
    while(pTmp != NULL) {
        if(pTmp->tar == tar){
            flag = false;
            break;
        }
        pTmp = pTmp->next;
    } 
   
    if(flag) {
        addEdge(src, tar, newAdj); 
    }
}

PEdge *rebuildMap(vector< vector<int> > &components, PEdge *old, vector<int> &newIndex, 
          vector<int> &newWeight, vector<int> &oldW) {
    PEdge *newTable = new PEdge[components.size()];
    for(int i = 0; i < components.size(); i++) {
        newTable[i] = NULL;
    }
    
    for(int k = 0; k < components.size(); k ++) {
        vector<int> comp = components[k];
        for(int i = 0; i < comp.size(); i ++ ) {
            newWeight[k] += oldW[comp[i]];

            // rebuild edges
            PEdge pTmp = old[comp[i]];
            while(pTmp != NULL) {
                if(k != newIndex[pTmp->tar]) { 
                    addEdgeToNewTable(k, newIndex[pTmp->tar], newTable);
                }
                pTmp = pTmp->next;
            } 
        }
    } 
    return newTable;
}

void getFinalAns(PEdge *adjTable, vector<int> &w, int src, int tar, vector<int> &maxSum) { 
    int tmp = maxSum[src] + w[tar];
    if(tmp > maxSum[tar]) {
        maxSum[tar] = tmp; 
    }
    PEdge pTmp = adjTable[tar];
    while(pTmp != NULL) {
        getFinalAns(adjTable, w, tar, pTmp->tar, maxSum); 
        pTmp = pTmp->next; 
    }
}

int main(){
    int n = 0;   // n nodes
    int m = 0;   // m edges
    cin>>n>>m;
    
    vector<int> w(n, 0);
    for(int i = 0; i < n; i ++) {
        cin>>w[i];
    }    

    // Adjcent table 
    PEdge * adjTable = new PEdge[n];
    
    for (int i = 0; i < m; i ++ ) {
        int src = 0; 
        int tar = 0;
        cin>>src>>tar;
        addEdge(src-1, tar-1, adjTable); 
    }  
    
    vector<int> newIndex(n, 0);
    vector< vector<int> > components = tarjan(n, adjTable, newIndex); 
    
    vector<int> newW(components.size(), 0);
    PEdge * newTable = rebuildMap(components, adjTable, newIndex, newW, w);

    vector<int> maxSum(components.size(), 0);
    int start = newIndex[0];
    maxSum[start] = newW[start];
    PEdge ptmp = newTable[start];
    while(ptmp != NULL ){
        getFinalAns(newTable, newW, start, ptmp->tar, maxSum); 
        ptmp = ptmp->next;  
    }
    
    int ans = 0;
    for(int i = 0; i < maxSum.size(); i++) {
        if(ans < maxSum[i]) {
            ans = maxSum[i];
        }
    }
    cout<<ans<<endl;
    return 0; 
}
