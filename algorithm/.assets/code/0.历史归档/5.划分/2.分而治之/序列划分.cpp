#include<cstdio>//最大值最小化
int a[(int)10E6],n,m;
int p(int x){
    int s=0,cnt=0;
    for(int i=0;i<n;i++){
        s+=a[i];
        if(s>=x){
            s=a[i];
            cnt++;
        }
    }
    return cnt<m;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)scanf("%d",a+i);
    int l=0,r=(int)10e9,m;
    while(l+1!=r){
        m=l+(r-l)/2;
        if(p(m))r=m;
        else l=m+1;
    }
    printf("%d\n",r);
    return 0;
}
/*
s<=10E9
input:
5 3
1 3 2 5 4
output:
7

*/
