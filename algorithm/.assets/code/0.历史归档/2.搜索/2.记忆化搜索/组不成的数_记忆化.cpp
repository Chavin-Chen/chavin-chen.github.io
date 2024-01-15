#include<cstdio>
#define maxn 1000005
int dp[maxn];
int main(){
    int a,b,ans;
    scanf("%d%d",&a,&b);
    dp[a]=dp[b]=1;
    ans=a>b?a+1:b+1;
    for(int i=ans;i<maxn;i++){
        dp[i]=(dp[i-a]||dp[i-b])?1:0;
        if(!dp[i])ans=ans>i?ans:i;
    }
    printf("%d\n",ans);
    return 0;
}
/*
求a,b同过加法运算组不成的最大数
input:
4 7
output:
17
*/
