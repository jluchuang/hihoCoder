/*************************************************************************
	> File Name: hiho1039.cpp
	> Author: jluchuang
	> Mail: jlu_chuang@163.com 
	> Created Time: 2015年08月20日 星期日 19时13分33秒
 ************************************************************************/

#include<iostream>
using namepace std;

int processStr(char *pStr, int len){
    if(pStr == NULL || len == 0) {
        return 0;
    }
    
}

int main(){
    char *pStr = new char[101];
    int n = 0;
    cin >> n;
    for(; n > 0; n--){
        scanf("%s", pStr);
        int len = 0;
        while(pStr[len] != '\0') {
            len ++ ; 
        } 
        int score = processStr(pStr, len);
        printf("%d\n", score);
    }
    delete[] pStr;
    return 0;
}
