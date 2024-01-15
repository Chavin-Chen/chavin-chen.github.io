#include<cstdio>//T(n)=2*T(n/2)+O(n),T(1)=1;T(n)=O(nlogn)
int a[100],n;
int split(int l,int r){
    if(l+1==r)return a[l];
    int i,s,ans,m=l+(r-l)/2,L=split(l,m),R=split(m,r);
    ans=L>R?L:R;
    for(s=0,i=m-1,L=a[i];i>=l;i--)
        L=L>(s+=a[i])?L:s;
    for(s=0,i=m,R=a[i];i<r;i++)
        R=R>(s+=a[i])?R:s;
    return ans>L+R?ans:L+R;
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",a+i);
    printf("%d\n",split(0,n));
    return 0;
}
/*
input:
7
4 5 -2 2 3 7 -11
output:
19

*/
