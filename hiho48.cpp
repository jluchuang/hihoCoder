/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho48.cpp
	Email: jlu_chuang@163.com
	Last modified: 2016-01-06 20:40
*****************************************************/

#include <iostream>
using namespace std; 

unsigned long long comps[100001][100001]; 
int inNum[100001];
int outNum[100001];  
unsigned long long virus[100001];
int flag[100001]; 

void deleteNode(int no) {
    for(int i = 0; i < outNum[no]; i++) {
        virus[comps[no][i]-1] += virus[no]; 
        inNum[comps[no][i]-1] -=  1; 
    }
}

int topologicalSorting(int n) {
    for(int j = 0; j < n-1; j ++) {
        for(int i = 0; i < n; i ++ ) {
            if(inNum[i] == 0 && flag[i] ==0) {
                flag[i] = 1; 
                deleteNode(i);
            }
        }
    }
    long long sum = 0;
    for(int i = 0; i < n; i ++ ) {
        sum += virus[i];
    }
    return (sum % 142857); 
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
        comps[a-1][outNum[a-1]]=b;
        outNum[a-1]++;
        inNum[b-1]++;
    }
    cout<<topologicalSorting(n);
    return 0;
}
