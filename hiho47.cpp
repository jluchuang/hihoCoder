/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho47.cpp
	Email: jlu_chuang@163.com
	Last modified: 2016-01-07 11:04
*****************************************************/
#include <iostream>
#include <vector>
#include <queue> 
using namespace std;

// AC 946ms

void topologicalSorting(int n, vector< vector<int> > &adj, vector<int> &indegree){
    queue<int> zeroQ;
    vector<int> flag(n, 0);
    
    for(int i = 0; i < n; i ++ ) {
        if(indegree[i] == 0) { 
            zeroQ.push(i);
        }
    }
    
    while(!zeroQ.empty()){
        int cur = zeroQ.front();
        flag[cur] = 1;
        for (int i = 0; i < adj[cur].size(); i++) {
            int tar = adj[cur][i]; 
            indegree[tar] -= 1; 
            if(indegree[tar] == 0) {
                zeroQ.push(tar);
            } 
        }
        zeroQ.pop();
    }
    
    for(int i = 0; i < n; i ++ ) {
        if(flag[i] == 0) { 
            cout<<"Wrong"<<endl;
            return;
        }
    }
    cout<<"Correct"<<endl;
}

int main() {
    int t = 0;
    cin>>t; 
    for(int i = 0; i < t; i ++ ) {
       int n = 0; 
       int m = 0; 
       cin>>n>>m;
       
       vector< vector<int> > adj(n, vector<int>()); 
       vector<int> indegree(n, 0);
       
       for(int j = 0; j < m; j ++) {
           int tar = 0; 
           int src = 0;
           cin>>src>>tar;
           adj[src-1].push_back(tar-1); 
           indegree[tar-1] += 1;
       }
       topologicalSorting(n, adj, indegree); 
    }
    return 0; 
}
