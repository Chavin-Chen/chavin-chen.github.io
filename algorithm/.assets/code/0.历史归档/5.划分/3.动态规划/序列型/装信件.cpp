#include<cstdio>
long long dp[100]={0,0,1};
int main(){
    int n;
    scanf("%d",&n);
    for(int i=3;i<=n;i++)
        dp[i]=(i-1)*(dp[i-2]+dp[i-1]);
    printf("%lld\n",dp[n]);
    return 0;
}
/*
È«´íÎ»ÅÅÁÐ;
input:
5
output:
44
*/
