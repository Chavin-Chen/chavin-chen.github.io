#include<cstdio>
int v[100],vis[10001]={1},d[10001]={0},n,s;
int dp(int i){
    if(vis[i])return d[i];
    vis[i]=1;d[i]=(1<<30);
    for(int j=0,t;j<n;j++)if(i>=v[j]){
        t=dp(i-v[j])+1;
        d[i]=((d[i]<t)?d[i]:t);
    }
    return d[i];
}
int start=1;
void print(int i){
    for(int j=0;j<n;j++)if(i>=v[j]&&d[i]==d[i-v[j]]+1){
        if(start){printf("%d",v[j]);start=0;}
        else printf(" %d",v[j]);
        print(i-v[j]);break;
    }
}
int main(){
    scanf("%d%d",&n,&s);
    for(int i=0;i<n;i++)scanf("%d",v+i);
    printf("%d\n",dp(s));
    print(s);printf("\n");
    return 0;
}
/*
input:
7 157
3 2 5 4 7 6 9
output:
18
4 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9

*/
