#include <cstdio>
#define maxn 20
int dp[maxn][maxn];
int main(){
    int m,n,ans=0;
    scanf("%d%d",&m,&n);
    for(int i=0;i<=m;i++)
        dp[i][0]=1;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=i;j++)
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
    printf("%d\n",dp[m][n]);
    return 0;
}
/*
һ�г���Ϊm+n������5Ԫ��Ʊ,����m�˳�5Ԫ,n�˳�10Ԫ,��ʼ����Ǯ,�����ҿ����Ŷ���(��ͬ��Ǯ���˻�����Ϊͬһ����)
����: ���m+n�˵Ķ���Ϸ�
	������һ��Ϊ5Ԫ,����ǰ��m-1��5Ԫ,n��10Ԫ
	������һ��Ϊ10Ԫ,��ǰ��m��5Ԫ,n-1��10Ԫ
dp[m][n] = dp[m-1][n] + dp[m][n-1];
dp[i][0] = 1; dp[m][m+i] = 0;
*/