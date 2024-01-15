#include<cstdio>
#include<cstring>
int dp[25][25],x,y,n,m;
void init(int x,int y){
    if(x<0||y<0||x>n||y>m)return ;
    dp[x][y]=0;
}
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d%d%d%d",&n,&m,&x,&y);
    init(x,y);
    init(x-2,y-1);init(x-2,y+1);
    init(x-1,y-2);init(x-1,y+2);
    init(x+1,y-2);init(x+1,y+2);
    init(x+2,y-1);init(x+2,y+1);
    int flag=1;
    for(int i=0;i<=n;i++){if(dp[i][0]==0)flag=0;dp[i][0]=flag;}
    flag=1;
    for(int i=0;i<=m;i++){if(dp[0][i]==0)flag=0;dp[0][i]=flag;}

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(dp[i][j])dp[i][j]=dp[i-1][j]+dp[i][j-1];

    printf("%d\n",dp[n][m]);
    return 0;
}
