#include<cstdio>
#include<algorithm>
int a[100],n,c;
int main(){
    scanf("%d%d",&n,&c);
    for(int i=0;i<n;i++)scanf("%d",a+i);
    std::sort(a,a+n);
    for(int i=0,s=0;s<=c;i++){
        s+=a[i];
        if(s>c){
            printf("%d %d\n",i,s-a[i]);
            break;
        }
    }
    return 0;
}
/*
选择尽量多的物体,总重不超过c
input:
5 7
1 3 2 5 4
output:
3 6

*/
