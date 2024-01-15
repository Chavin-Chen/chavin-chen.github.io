#include<cstdio>
#include<algorithm>
struct X{
    int w,v;
    bool operator <(const X&x)const{
        return 1.0*v/w>1.0*x.v/x.w;
    }
}a[100];
int main(){
    int n,c;
    double v=0;
    scanf("%d%d",&n,&c);
    for(int i=0;i<n;i++)scanf("%d%d",&a[i].w,&a[i].v);
    std::sort(a,a+n);
    for(int i=0,s=0;;i++){
        if(s+a[i].w>c){
            v+=(c-s)*((1.0*a[i].v)/a[i].w);
            break;
        }
        s+=a[i].w;
        v+=a[i].v;
    }
    printf("%.2lf\n",v);
    return 0;
}
/*
input:
5 7
1 4
3 6
2 5
5 9
4 4
output:
16.80
*/
