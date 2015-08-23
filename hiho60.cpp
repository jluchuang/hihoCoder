/*************************************************************************
	> File Name: hiho60.cpp
	> Author: jluchuang
	> Mail: jlu_chuang@163.com 
	> Created Time: 2015年08月23日 星期日 20时50分57秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

int get_max(int a, int b) {
	return (a > b) ? a : b ;
} 

int matchingContentLength(string str1, string str2){
	if(str1.length() < 3 || str2.length() < 3) { 
		return 0;
	}
	int len1 = str1.length();
	int len2 = str2.length();
	vector < vector<int> > dp(len1, vector<int>(len2, 0));
	vector < vector<int> > commonLen(len1, vector<int>(len2, 0));

	// Initialize commentLen
	for(int i = 0; i < len1; i++) {
		if(str1[i] == str2[0]) { 
			commonLen[i][0] = 1; 
		}
	}
	for(int i = 0 ; i < len2; i++){
		if(str1[0] == str2[i]) { 
			commonLen[0][i] = 1;
		}
	}
	
	// Start DP
	for(int i = 1; i < len1; i++) { 
		for(int j = 1; j < len2; j++) {
			// Get commonLen
			commonLen[i][j] = 0;
			if(str1[i] == str2[j]) {
				commonLen[i][j] = commonLen[i-1][j-1] + 1;
			}

			if(commonLen[i][j] >= 3) {
				if(i == (commonLen[i][j] - 1) || j == (commonLen[i][j] - 1) ) {
					dp[i][j] = commonLen[i][j];
				}
				else { 
					dp[i][j] = dp[i-commonLen[i][j]][j-commonLen[i][j]] + commonLen[i][j];
					dp[i][j] = get_max(dp[i-3][j-3] + 3, dp[i][j]); 
				}
				/*for(int k = 3; k < commonLen[i][j]; k++) { 
					int tmp	= dp[i-k][j-k] + k;
					dp[i][j] = get_max(tmp, dp[i][j]);
 				}*/
			}

			int tmp = get_max(dp[i][j-1], dp[i-1][j]); 
			dp[i][j] = get_max(tmp, dp[i][j]);
		}
	}

	return dp[len1-1][len2-1];
}

int main(){
	string str1;
	string str2;
	cin>>str1;
	cin>>str2;
	cout<<matchingContentLength(str1, str2)<<endl;
	return 0;
}

