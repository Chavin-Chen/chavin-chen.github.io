#include<cstdio>//选最少的区间覆盖线段[s,t]
#include<algorithm>
struct Line{
    int a,b;
    bool operator < (const Line&x)const{
        return a<x.a;
    }
}a[100];
void deal(int s,Line*a,int n){
    for(int i=0;i<n;i++)
        a[i].a=(a[i].a<s)?s:a[i].a;
}
int main(){
    int n,s,t,cnt=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d%d",&a[i].a,&a[i].b);
    scanf("%d%d",&s,&t);
    std::sort(a,a+n);
    deal(s,a,n);
    for(int i=0,e=s;i<n;i++){
        if(a[i].a==s){
            e=a[i].b>e?a[i].b:e;
        }else{
            //printf("e=%d ai=%d,bi=%d\n",e,a[i].a,a[i].b);
            if(a[i].a>e){cnt=-1;break;}
            else {e=a[i].b;cnt++;}
            if(e>=t)break;
            s=e; deal(s,a,n);
            cnt++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
/*
input:
6
1 4
2 4
3 5
4 7
6 8
8 10
2 9
output:
3
test0.in
4
2 5
1 4
6 8
7 10
3 9
test0.out
-1
*/
