#include<cstdio>
long long dp[100]={0,1,1};
int main(){
    int n;
    scanf("%d",&n);
    for(int i=3;i<=n;i++)
        dp[i]=dp[i-1]+dp[i-2];
    printf("%lld\n",dp[n]);
    return 0;
}
/*
n个台阶,从第一阶开始,一步上一阶或两阶,共几种上法
input:
10
output:
55

*/