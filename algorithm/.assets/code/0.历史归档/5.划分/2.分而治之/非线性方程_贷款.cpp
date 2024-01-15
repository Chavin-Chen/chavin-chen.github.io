#include<cstdio>
int main(){
    double a,c,m,l=0,r=100,f;
    int b;
    scanf("%lf%d%lf",&a,&b,&c);
    while(r-l>1e-5){
        m=l+(r-l)/2;
        f=a;
        for(int i=0;i<b;i++)f+=f*m/100.0-c;
        if(f-0>=1e-5)r=m;
        else l=m;
    }
    printf("%.3lf%%\n",m);
    return 0;
}
/*
input:
2000 4 510
output:
0.797%

*/
