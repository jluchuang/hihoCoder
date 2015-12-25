/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho11.cpp
	Email: jlu_chuang@163.com
	Last modified: 2015-12-24 18:48
*****************************************************/

#include <iostream>
#include <string.h>
using namespace std; 

typedef struct TreeEdge {
    int no; 
    struct TreeEdge * next; 
    TreeEdge(int _no) {
        this->no = _no; 
        this->next = NULL; 
    }
} Edge; 

typedef Edge * PEdge;

void addEdge(PEdge * pTree, int s, int t) {
    if(pTree[s] == NULL) {
        pTree[s] = new Edge(t);
    }
    else {
        PEdge topS = pTree[s]; 
        while(topS->next != NULL) {
            topS = topS->next; 
        } 
        topS->next = new Edge(t); 
    }
}
int getMaxLen(PEdge * pTree, int no, int* backFlag, int &maxLen) {
    int maxHeight = 0;
    int secHeight = 0;
    
    //cout<<"current Node No : "<<no<<endl;   
    backFlag[no] = 1; 
    PEdge topNo = pTree[no]; 
    while(topNo != NULL) { 
        
        if(backFlag[topNo->no] == 0) {
            int temp = getMaxLen(pTree, topNo->no, backFlag, maxLen) + 1;
            //cout<< temp <<endl; 
            if(temp > maxHeight) { 
                secHeight = maxHeight; 
                maxHeight = temp; 
            } 
            else {
                if(temp > secHeight) {
                    secHeight = temp; 
                }
            }
        }
        topNo = topNo->next; 
    }
    
    if(secHeight + maxHeight > maxLen) {
        maxLen = secHeight + maxHeight; 
    }    

    return maxHeight; 
}

int main() {
    int n = 0; 
    cin>>n; 
    PEdge *pTree = new PEdge[n]; 

    for(int i = 0; i < n-1; i ++) {
        int s = 0;
        int t = 0; 
        cin>>s>>t; 
       
        addEdge(pTree, s-1, t-1); 
        addEdge(pTree, t-1, s-1); 
    }
    //cout<<"built tree"<<endl;
    int res = 0;
    int *backFlag = new int[n];
    memset(backFlag, 0, sizeof(int) * n); 
    getMaxLen(pTree, 0, backFlag, res); 
    cout<<res<<endl;
     
    return 0; 
}
