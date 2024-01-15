#include<cstdio>//矩阵A*B*C满足结合律,运算量为p[i-1]*p[i]*p[j](第i矩阵为p[i-1]*p[i])
int d[101][101],p[101];
int dp(int i,int j){
    if(i==j||d[i][j]>0)return d[i][j];
    if(i+1==j)return d[i][j]=p[i-1]*p[i]*p[j];
    int minn=1<<30;
    for(int k=i+1,l,r;k<j;k++){//最后乘法的位置
        l=dp(i,k);r=dp(k+1,j);
        minn=(minn<l+r+p[i-1]*p[k]*p[j])?minn:l+r+p[i-1]*p[k]*p[j];
    }
    return d[i][j]=minn;
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<=n;i++)scanf("%d",p+i);
    printf("%d\n",dp(1,n));
    return 0;
}
/*
input:
3
2 3 4 5

output:
64

*/
