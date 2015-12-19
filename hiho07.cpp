#include <iostream>
#include <string.h>
using namespace std; 

int main(){ 
    int dp[100010];
    int need[501];
    int value[501];
  
    int n = 0; 
    int m = 0;
    cin>>n;
    cin>>m;

    memset(dp, 0, sizeof(int)*100010);
    memset(need, 0, sizeof(int)*501);
    memset(value, 0, sizeof(int)*501); 

    for(int i = 0; i < n; i++) {
        cin>>need[i];
	cin>>value[i];
    }

    for(int i = 1; i <= n; i ++) {
        for(int j = need[i-1]; j <= m; j++ ) {
	    int temp = dp[j-need[i-1]] + value[i-1];
	    if(temp > dp[j]) {
	        dp[j] = temp;
	    }
	}
    }
    
    cout<<dp[m]<<endl;
    return 0;
}
