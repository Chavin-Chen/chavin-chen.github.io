#include<cstdio>
long long ans[100];
int main(){
    int n;
    scanf("%d",&n);
    ans[3]=1;
    for(int i=4;i<=n;i++)
        ans[i]=2*ans[i-1]+(1<<(i-4))-ans[i-4];
    printf("%lld\n",ans[n]);
    return 0;
}
/*
一行序列摆放U,L,至少三个U连续,对第一个三连续U分类
f(i)=已经合法+必须摆放U才合法(i-3)为L:2*f(i-1)+2^(i-4)-f(i-4);
input:
30
output:
974791728

*/
