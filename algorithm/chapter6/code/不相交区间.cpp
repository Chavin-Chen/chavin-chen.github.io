#include<cstdio>//选择尽量多的开区间,两两没有交点
#include<algorithm>
struct Line{
    int a,b;
    bool operator < (const Line&x)const{
        return b<x.b;
    }
}a[100];
int main(){
    int n,cnt=1;
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d%d",&a[i].a,&a[i].b);
    std::sort(a,a+n);
    for(int i=0,t=a[i].b;i<n;i++){
        if(a[i].a>=t){
            t=a[i].b;cnt++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
/*
input:
5
1 4
2 3
4 7
5 8
6 9
output:
2

*/
