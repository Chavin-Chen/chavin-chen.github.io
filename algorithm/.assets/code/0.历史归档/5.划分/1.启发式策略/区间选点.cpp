#include<cstdio>//ѡ�����ٵĵ�ʹ�����б����䶼��ѡ��
#include<algorithm>
struct Line{
    int a,b;
    bool operator < (const Line&x)const{
            return b!=x.b?b<x.b:a>x.a;//ͬ�ҽ���
    }
}a[100];
int main(){
    int n,cnt=1;
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d%d",&a[i].a,&a[i].b);
    std::sort(a,a+n);
    for(int i=0,t=a[i].b;i<n;i++){
        if(a[i].a>t){
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
0 5
2 5
5 7
8 9
output:
3

*/
