#include <iostream>
#include <string>
using namespace std;

int judgeEqual(const string s, int head, int tail);

int getMaxPalindrome(const string s) {
    int max = 1;
    for(int i = 0; i < s.length(); i ++ ) {
        // s[i] in center
	int temp = judgeEqual(s, i-1, i+1) + 1;

	if(temp > max) {
	    max = temp; 
	}

        temp = judgeEqual(s, i,i+1);
        if(temp > max) {
	    max = temp;
	}
	
    }
    return max;
}

int judgeEqual(const string s, int head, int tail) {
    int temp = 0;
    while(head >= 0 && tail < s.length() && s[tail] == s[head]) {
	temp += 2;
	head --;
	tail ++;
    }
    return temp;
}

int main(){
    int n = 0;
    cin>>n;

    for(int i = 0; i < n; i ++) {
        string s;
	cin>>s;
	cout<<getMaxPalindrome(s)<<endl;
    }

    return 0;
}
