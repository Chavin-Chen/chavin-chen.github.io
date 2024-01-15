#include<cstdio>
int  dfs(int n,int m){
    if(n<m)return 0;
    if(n==m)return 1;
    if(m==0)return 1;
    return dfs(n-1,m-1)+dfs(n-1,m);//对于一个特殊x,取或不取结果相加
}
int main()
{
    int ans=dfs(10,3);
    printf("%d\n",ans);
    return 0;
}
