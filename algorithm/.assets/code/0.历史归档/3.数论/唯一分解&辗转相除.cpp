#include<cstdio>
int x[100],n;//唯一分解定理:任何一个数都可以分解成素数p^ai,分解表唯一
int gcd(int a, int b) {  //唯一分解定理->辗转相除法
    return !b ? a : gcd(b, a % b);  //递归层数4.785lg(max{a,b})+1.67 --fibonacci
}
int main(){
    int i;
    while(scanf("%d",&n)){
        for(i=0;i<n;i++)scanf("%d",x+i);//?可变计算顺序的除法表达式可表示成A/B: x0/(x1/x2...xn) => (x0*x2*x3..xn)/x1
        x[1]/=gcd(x[1],x[0]);
        i=2;
        while(x[1]!=1&&i<n){
            x[1]/=gcd(x[i++],x[1]);
        }
        if(x[1]==1)printf("yes\n");
        else printf("no\n");
    }
    return 0;
}
/*
input:
4
1 2 1 2
4
7 5 3 2
output:
yes
no
*/
