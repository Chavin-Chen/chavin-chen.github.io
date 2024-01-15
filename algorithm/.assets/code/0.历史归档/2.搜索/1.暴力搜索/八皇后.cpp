#include<cstdio>
int c[20],ans,n;
void backtrack(int k){
    if(k==n){
        ans++;
    }else for(int i=0;i<n;i++){
        int ok=1;
        c[k]=i;
        for(int i=0;i<k&&ok;i++)
            if(c[k]==c[i]||c[i]-i==c[k]-k||i+c[i]==k+c[k])ok=0;
        if(ok)backtrack(k+1);
    }
}
int main(){
    while(scanf("%d",&n)!=-1){
        ans=0;
        backtrack(0);
        printf("%d\n",ans);
    }
    return 0;
}
/*
input:
4
8
output:
2
92

*/