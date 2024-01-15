#include<cstdio>
long long  a[100];
int main(){
    int n;
    scanf("%d",&n);
    a[2]=a[3]=1;
    for(int i=4;i<=n;i++){
        a[i]=0;
        for(int k=2;k<i;k++)
            a[i]+=a[k]*a[i-k+1];
    }
    printf("%lld\n",a[n]);
    return 0;
}
/*
catalan
一个凸n边形,用n-3条不相交对角线划分成n-2个三角形的总划分方法
input:
8
output:
132

*/
