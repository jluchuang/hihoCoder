/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho79.cpp
	Email: jlu_chuang@163.com
	Last modified: 2016-01-08 14:07
*****************************************************/
#include <iostream> 
#include <stack>
#include <vector>
#include <set>
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
bool finalAns; 
int nodeNum;

void tarjan(int v, PEdge *adjTable, stack<int> &dfsS, 
         vector<int> &index, vector<int> &lowIndex, 
         vector<int> &inStack, vector< set<int> > &res);

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

void addEdge(int src, int tar, int status, PEdge *adjTable, int n) {
    if(status == 1) {
        addEdge(src+n, tar, adjTable );    // If src is 1, then tar must 0
        addEdge(tar+n, src, adjTable );    // If tar is 1, then src must 0
    }
    else {
        // status is 0
        addEdge(src, tar+n, adjTable);     // If src is 0, then tar must 1
        addEdge(tar, src+n, adjTable);     // If tar is 0, then src must 1
    }
}

bool checkInSet(int v, set<int> &component) {
    if(v < nodeNum) {
        v += nodeNum;
    }
    else {
        v -= nodeNum;
    }
    
    set<int>::iterator it = component.find(v); 
    if(it != component.end()) {
        return true;
    } 
    else {
        return false;
    }
}

vector< set<int> > tarjan(int n, PEdge *adjTable){
    stack<int> dfsS; 
    vector<int> inStack(n, 0);
    vector<int> index(n, -1); 
    vector<int> lowIndex(n, 0);
    vector< set<int> > res;
    
    curIndex = 1; 
    for(int i = 0; i < n; i ++) {
        //if(finalAns == false) {
        //    return res;
        //}
        if(index[i] == -1) {
            tarjan(i, adjTable, dfsS, index, lowIndex, inStack, res); 
        }
    }
    return res;
}


void tarjan(int v, PEdge *adjTable, stack<int> &dfsS, 
         vector<int> &index, vector<int> &lowIndex, 
         vector<int> &inStack, vector< set<int> > &res) {
    //if(finalAns == false) {
    //    return;
    //}
    index[v] = lowIndex[v] = curIndex;
    curIndex ++;
    inStack[v] = 1; 
    dfsS.push(v);
     
    PEdge pTmp = adjTable[v]; 
    while(pTmp != NULL) {
        int tar = pTmp->tar;
        if(index[tar] == -1) {
             tarjan(tar, adjTable, dfsS, index, lowIndex, inStack, res);
             //if(finalAns == false) {
             //    return;    
             //}
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
        set<int> component;
        component.insert(v); 
        while(v != dfsS.top()) {
            //if(checkInSet(dfsS.top(), component)) {
            //    finalAns = false;
            //    return; 
            //}   
            component.insert(dfsS.top());
            inStack[dfsS.top()] == 0;
            dfsS.pop();
        }
        dfsS.pop();
        inStack[v] = 0;
        res.push_back(component);
    }
}

void clearTable(int size, PEdge *adjTable) {
    for(int i = 0; i < size; i ++ ){
        PEdge ptmp = adjTable[i];
        while(ptmp != NULL) {
            PEdge pnext = ptmp->next;
            delete ptmp;
            ptmp = pnext; 
        }
    }
    
    delete[] adjTable;
}

bool check(vector<set<int> > components) {
    for(int i = 0; i < components.size(); i ++){
        set<int> comp = components[i];
        for(set<int>::iterator it = comp.begin(); it != comp.end(); it ++) {
            int v = *it;
            if(v >= nodeNum) {
                v -= nodeNum;
            }
            else {
                v += nodeNum;
            }
            set<int>::iterator sIt = comp.find(v);
            if(sIt != comp.end()) {
                return false;
            }
        }
    }
    return true;
}

int main(){
    int t = 0; 
    cin>>t;
    for(int tNo = 0; tNo < t; tNo ++){ 
        int n = 0;   // n nodes
        int m = 0;   // m edges
        cin>>n>>m;

        // Initialize global
        nodeNum = n;
        curIndex = 0;
     
        // Adjcent table 
        PEdge * adjTable = new PEdge[n*2];
        for(int i = 0; i < n*2; i ++){
            adjTable[i] = NULL;
        }
    
        for (int i = 0; i < m; i ++ ) {
            int src = 0; 
            int tar = 0;
            int status = 0;
            cin>>src>>tar>>status;
            addEdge(src-1, tar-1, status, adjTable, n); 
        }  
        
        //cout<<" start case "<<tNo+1<<endl;
        finalAns = true;
        vector< set<int> > res = tarjan(n*2, adjTable); 
    
        if(check(res)) {
            cout<<"Yes"<<endl;
        }
        else {
            cout<<"No"<<endl;
        }
        // cout<<"============================components================================="<<endl;
        // for(vector< set<int> >::iterator it = res.begin(); it != res.end(); it ++) {
        //    set<int> comp = *it; 
        //    cout<<"{";
        //    for(set<int>::iterator comIt = comp.begin(); comIt != comp.end(); comIt ++){
        //        cout<<' '<< *comIt;
        //    }
        //    cout<<" }"<<endl; 
        //}
        // cout<<"======================================================================="<<endl;
        clearTable(n*2, adjTable);
        //cout<<" end case "<<tNo+1<<endl; 
    }
    return 0; 
}
