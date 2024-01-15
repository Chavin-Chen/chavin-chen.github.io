#define Local
#include<cstdio>
#include<cstring>
char vis[876543210],ss[10];
struct Node{
    int s;
    int dist;
}q[100000];
int ap=0,target=0,init=0;
int moves(int s,int dir){
    char t;
    sprintf(ss,"%09d",s);
    int x=(strchr(ss,'0')-ss),ans;
    switch(dir){
        case 1:t=ss[x];ss[x]=ss[x+3];ss[x+3]=t;break;
        case 2:t=ss[x];ss[x]=ss[x-1];ss[x-1]=t;break;
        case 3:t=ss[x];ss[x]=ss[x-3];ss[x-3]=t;break;
        case 4:t=ss[x];ss[x]=ss[x+1];ss[x+1]=t;break;
    }
    sscanf(ss,"%d",&ans);
    return ans;
}
int can_move(int dir,int s){//dir:1234 down left up right
    sprintf(ss,"%d",s);
    int x=(strchr(ss,'0')-ss)/3,y=(strchr(ss,'0')-ss)%3;
    if((dir==1&&x==2)||(dir==2&&y==0)||(dir==3&&x==0)||(dir==4&&y==2))return 0;
    int t=moves(s,dir);
    if(vis[t])return 0;
    return t;
}
int ok=0;
void bfs(int i){
    if(ok||vis[q[i].s])return ;
    vis[q[i].s]=1;
    if(q[i].s==target){
        ok=1;
        printf("%d\n",q[i].dist);
    }
}
int main(){
    #ifdef Local
        freopen("in.txt","r",stdin);
    #endif // Local
    int dt;char ct;
    do{scanf("%d%c",&dt,&ct);init=init*10+dt;}while(ct!='\n');
    do{scanf("%d%c",&dt,&ct);target=target*10+dt;}while(ct!='\n');
    q[ap].s=init;q[ap++].dist=0;
    for(int i=0;i!=ap&&!ok;i=(i+1)%100000){
        bfs(i);
        for(int j=1,ms;j<=4;j++){
            if(ms=can_move(j,q[i].s)){
                q[ap].s=ms;
                q[ap].dist=q[i].dist+1;
                ap=(ap+1)%100000;
            }
        }
    }
    if(!ok)printf("-1\n");
    return 0;
}
/*
time:3s
input:
0 2 6 4 1 3 7 5 8
0 8 1 5 7 3 6 4 2
-
2 6 4 1 3 7 0 5 8
8 1 5 7 3 6 4 0 2
-
1 2 3 4 5 6 7 8 0
1 2 3 4 5 6 8 7 0

output:
26
-
31
-
-1

*/
