#include<cstdio>
int a[20],n,ans[20];
int sea(int k){
    if(k==n){
        for(int i=0;i<n;i++)
            printf((i==n-1)?"%d\n":"%d ",ans[i]);
    }else for(int i=0;i<n;i++){
        int ok=1;
        for(int j=0;j<k&&ok;j++)if(ans[j]==a[i])ok=0;
        if(ok){
            ans[k]=a[i];
            sea(k+1);
        }
    }
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",a+i);
    sea(0);
    return 0;
}
/*
input:
4
15 16 27 89
output:
15 16 27 89
15 16 89 27
15 27 16 89
15 27 89 16
15 89 16 27
15 89 27 16
16 15 27 89
16 15 89 27
16 27 15 89
16 27 89 15
16 89 15 27
16 89 27 15
27 15 16 89
27 15 89 16
27 16 15 89
27 16 89 15
27 89 15 16
27 89 16 15
89 15 16 27
89 15 27 16
89 16 15 27
89 16 27 15
89 27 15 16
89 27 16 15

*/
