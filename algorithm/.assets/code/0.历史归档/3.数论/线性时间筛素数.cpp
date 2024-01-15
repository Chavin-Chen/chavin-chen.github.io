#include<iostream>
#include<cmath>
using namespace std;
#define MAXN 1000005
bool t[MAXN];//1表示非质数
int main(){
	int * a = new int[(int)(MAXN/log(MAXN)*1.5)] , ap=0;
    for(long long i=2;i<MAXN;i++){
        if(!t[i]) a[ap++]=i;   //添加到素数队列,a,b,c...
        for(int j=0;j<ap&&i*a[j]<MAXN;j++){
            t[ i*a[j] ]=1;// 当前数和已找到的素数的积非质
            if( !(i % a[j]) ) break;//若当前数非素a*x,那么不必再继续筛a*x*b,因为其另一个因子a*x会再素数为b的时候筛掉abx
        }
    }

    for(int i=0;i<ap;i++)
        cout<<a[i]<<" ";
    cout<<endl;

    return 0;
}
/*
100 25
1000 168
10000 1229
100000 9592
1000000 78498
10000000 664579
100000000 5761455
*/
