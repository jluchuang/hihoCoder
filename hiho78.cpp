/****************************************************
	coding: utf-8
	Author: jluchuang
	File Name: hiho78.cpp
	Email: jlu_chuang@163.com
	Last modified: 2015-12-28 14:37
*****************************************************/
#include <iostream> 
using namespace std; 

typedef struct TrieNode {
    int preNum; 
    struct TrieNode *pNode[26]; 
    bool endFlag; 
    TrieNode(int _preNum, bool _endFlag) {
        preNum = _preNum; 
        endFlag = _endFlag; 
        for(int i = 0; i < 26; i ++) {
            pNode[i] == NULL;
        } 
    }
} TNode;


