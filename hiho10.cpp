/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho10.cpp
	Email: jlu_chuang@163.com
	Last modified: 2015-12-24 18:02
*****************************************************/

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef struct TreeNode {
    char name; 
    struct TreeNode *pl;
    struct TreeNode *pr;
    
    TreeNode(char _name){
        this->name = _name; 
    }  
} Node; 

Node * getRoot(char *pre, char *mid, int preStart, int midStart, int len) {
    Node *pNode = new Node(pre[preStart]);
    
    int leftLen = 0;
    for(int i = midStart; i < midStart + len; i ++) {
        if(pNode->name == mid[i]) {
            break;
        }
        leftLen ++;
    } 
    
    if(leftLen != 0) { 
        pNode->pl = getRoot(pre, mid, (preStart + 1), midStart, leftLen); 
    }
    else {
        pNode->pl = NULL;
    }
    
    if((len - leftLen - 1) > 0) {
        pNode->pr = getRoot(pre, mid, (preStart + 1 + leftLen), (midStart + leftLen + 1 ), (len - leftLen - 1));
    }
    else {
        pNode->pr = NULL;
    }     

    return pNode;
} 

void postTravel(Node * pt) {
    if(pt->pl != NULL) {
        postTravel(pt->pl); 
    }
    if(pt->pr != NULL) {
        postTravel(pt->pr); 
    }
    cout<<pt->name;
}

int main() {
    char preStr[26];
    char midStr[26];
    cin>>preStr;
    cin>>midStr;
    Node *pTree = getRoot(preStr, midStr, 0, 0, strlen(preStr)); 
    postTravel(pTree);
    cout<<endl;  
    return 0; 
}
