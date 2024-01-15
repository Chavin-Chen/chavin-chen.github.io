#include<cstdio>
#include<algorithm>
int a[10000],n;
int lower_bound(int left,int right,int key){//<algorithm>std::lower_bound(array,array+len,key)
    int m;
    while(left<right){
        m=left+(right-left)/2;
        if(a[m]>=key)right=m;
        else left=m+1;
    }
    return left;
}
int upper_bound(int left,int right,int key){//return:a[i]==key?[,x):move i>x rearer one,keep sorted!
    int m;
    while(left<right){
        m=left+(right-left)/2;
        if(a[m]<=key)left=m+1;
        else right=m;
    }
    return left;
}
int main(){
    int m,A,B;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)scanf("%d",a+i);
    std::sort(a,a+n);
    while(m--){
        scanf("%d%d",&A,&B);
        printf("%d\n",upper_bound(0,n,B)-lower_bound(0,n,A));
    }
    return 0;
}
/*
count for [a,b]
intput:
7 5
4 12 11 24 11 33 33
0 100
4 11
12 33
33 34
34 35
output:
7
3
4
2
0

*/
