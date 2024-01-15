#include<cstdio>
int n,len,cnt,ok=0;
char s[1000];
void dfs(int x){
    if(ok)return ;
    if(cnt++ == n){
        ok=1;s[x]=0;
        puts(s);
    }else for(int i=0,ok;i<len;i++){
        s[x]=i+'A';
        ok=1;
        for(int j=1,eq;j<=(x+1)/2&&ok;j++){
            eq=1;
            for(int k=0;k<j&&eq;k++)
                if(s[x-k]!=s[x-j-k])eq=0;
            if(eq)ok=0;
        }
        if(ok)dfs(x+1);
    }
}
int main(){
    while(scanf("%d%d",&n,&len)!=-1){
        cnt=ok=0;
        dfs(0);
    }
    return 0;
}
/*
前len个字母,第n个困难序列
input:
7 3
30 3
output:
ABACABA
ABACABCACBABCABACABCACBACABA

*/
