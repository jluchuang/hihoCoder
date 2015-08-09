/*************************************************************************
	> File Name: hiho58.cpp
	> Author: jluchuang
	> Mail: jlu_chuang@163.com 
	> Created Time: 2015年08月09日 星期日 20时42分33秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct LetterN{
	char c;
	int n;
	LetterN(){
		n = 0;
	}
	LetterN(char _c, int _n){
		c = _c;
		n = _n;
	}
};

void computeLetterN(vector <LetterN> & letterNList, string str){
	if(str.length() == 0){
		return;
	}
	LetterN *ptmp = new LetterN(str[0], 0);
	for(int i = 0; i < str.length(); i++){
		if(str[i] == ptmp->c){
			ptmp->n ++;
		}
		else{
			letterNList.insert(letterNList.end(), *ptmp);
			ptmp->c = str[i];
			ptmp->n = 1;
		}
	}
	letterNList.insert(letterNList.end(), *ptmp);
	delete ptmp;
}

bool check(vector <LetterN> & letterNList){
	//for(int i = 0; i < letterNList.size(); i++){
	//	cout<<"("<<letterNList[i].c<<", "<<letterNList[i].n<<")";
	//}
	//cout<<endl;
	if(letterNList.size()<=2){
		return false;
	}
	for(int i = 0; i <= letterNList.size()-3; i++){
		if(letterNList[i].c == letterNList[i+1].c-1 && letterNList[i+1].c == letterNList[i+2].c-1){
			if(letterNList[i].n >= letterNList[i+1].n && letterNList[i+1].n <= letterNList[i+2].n){
				return true;
			}
		}
	}
	return false;
}

int main(){
	int ncase = 0;
	cin >> ncase;
	for(int i = 0; i < ncase; i++){
		int length;
		cin>>length;
		string checkStr;
		cin >> checkStr;
		vector<LetterN> letterNList;
		computeLetterN(letterNList, checkStr);
		if(check(letterNList)){
			cout<<"YES"<<endl;
		}
		else{
			cout<<"NO"<<endl;
		}
		letterNList.clear();
	}
	return 0;
}


