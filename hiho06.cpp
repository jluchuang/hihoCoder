#include <stdio.h>

// AC 135ms

const int MAX = 100005;

int dp[MAX];
int need[505],value[505];

int main()
{
    int  N,M;
    int i,j,tmp;
    scanf("%d%d",&N,&M);
    for (i=0; i<N; ++i)
    {
        scanf("%d%d",need+i,value+i);
    }

    for (i=0; i<N; ++i)
    {
        for (j=M; j>=need[i]; --j)
        {
            tmp = dp[j-need[i]] + value[i];
            if (tmp > dp[j]) dp[j] = tmp;
        }
    }
    printf("%d\n",dp[M]);
    return 0;
}
