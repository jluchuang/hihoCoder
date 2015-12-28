/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho78.cpp
	Email: jlu_chuang@163.com
	Last modified: 2015-12-28 14:37
*****************************************************/
#include <iostream>
#include <string> 
using namespace std; 

#define CNUM 26        // Character numbers
#define PRE_TOP 5     

typedef struct TrieNode {
    int preNum; 
    struct TrieNode *pNode[CNUM]; 
    bool endFlag; 
    TrieNode(int _preNum, bool _endFlag) {
        preNum = _preNum; 
        endFlag = _endFlag; 
        for(int i = 0; i < CNUM; i ++) {
            pNode[i] = NULL;
        } 
    }
} TNode;

void addWordToTree(string word, TNode* root) {
    TNode *temp = root; 
    for(int i = 0; i < word.length(); i ++) {
        int index = word[i]-'a'; 
        if(temp->pNode[index] == NULL) {
            temp->pNode[index] = new TNode(0, false); 
        }
        temp->preNum ++; 
        temp = temp->pNode[index]; 
    }
    temp->endFlag = true;
}

void dfsGetAns(TNode *root, int &ans) {
    if(root->preNum <= PRE_TOP) {
        ans ++;
        return;  
    }
    for(int i = 0; i < CNUM; i ++) {
        if(root->pNode[i] != NULL){
            dfsGetAns(root->pNode[i], ans); 
        }
    }
}

int main() {
    int n = 0;
    cin>>n; 

    TNode * tree = new TNode(0, false); 
    for(int i = 0; i < n; i ++) {
        string temp;
        cin>>temp; 
        addWordToTree(temp, tree); 
    }
    
    int ans = 0;
    for(int i = 0; i < CNUM; i ++) {
        if(tree->pNode[i] != NULL) {
            dfsGetAns(tree->pNode[i], ans); 
        }
    }
    cout<<ans<<endl;
    return 0;
}
  
