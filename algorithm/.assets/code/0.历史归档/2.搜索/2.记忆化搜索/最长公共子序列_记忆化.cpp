#include<cstdio>
#include<cstring>
#include<algorithm>
char s[101],t[101];
int dp[101][101];
int main()
{
    scanf("%s%s",s,t);
    for(int i=strlen(s)-1;i>=0;i--)
        for(int j=strlen(t)-1;j>=0;j--)
            if(s[i]==t[j])dp[i][j]=dp[i+1][j+1]+1;
            else dp[i][j]=std::max(dp[i+1][j],dp[i][j+1]);
    printf("%d\n",dp[0][0]);
    return 0;
}