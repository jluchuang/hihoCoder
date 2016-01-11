/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho80.cpp
	Email: jlu_chuang@163.com
	Last modified: 2016-01-11 11:02
*****************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std; 

#define COLOR_NUM 3

vector<int> c(COLOR_NUM, 0); 
vector<int> condition(COLOR_NUM, 0); 

bool compareFunction(int a, int b) {
    return (a<b); 
}

bool check() {
    vector<int> diff(3, 0); 
    diff[0] = abs(c[0] - c[1]); 
    diff[1] = abs(c[1] - c[2]);
    diff[2] = abs(c[2] - c[0]);
    sort(diff.begin(), diff.end(), compareFunction); 
    if(diff[0] == condition[0] && diff[1] == condition[1] && diff[2] == condition[2])  {
        return true; 
    }
    return false;
}

int getCurrentCount(char ball) {
    switch (ball) {
        case 'R': { 
            c[0] ++;
            break; 
        }
        case 'Y': {
            c[1] ++;
            break; 
        }
        case 'B': {
            c[2] ++; 
            break; 
        }
    }
    int curNum = c[0] + c[1] + c[2];
    if(check()) {
        for(int i = 0; i < c.size(); i++) {
            c[i] = 0;
        }
    }
    return curNum;
}

int main() {
  
    cin>>condition[0]>>condition[1]>>condition[2];
    sort(condition.begin(), condition.end(), compareFunction); 
    getchar(); 
    char ball;
    int max_num = 0;
    ball = getchar(); 
    while(ball != '\n') {
        //cout<<ball;
        int cur = getCurrentCount(ball); 
        if(max_num < cur) {
            max_num = cur;
        }
        ball = getchar(); 
        //cout<<max_num<<endl;
    }
    cout<<max_num<<endl;
    return 0;
}
