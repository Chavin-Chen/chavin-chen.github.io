#include<cstdio>
#include<algorithm>
int a[100],n,c;
int main(){
    int ans=0;
    scanf("%d%d",&n,&c);
    for(int i=0;i<n;i++)scanf("%d",a+i);
    std::sort(a,a+n);
    for(int i=0,j=n-1;i<=j;j--){
        ans++;
        if(a[i]+a[j]<=c)i++;
    }
    printf("%d\n",ans);
    return 0;
}
/*
input:
7 10
8 4 9 5 5 7 3
output:
5

*/
