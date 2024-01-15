#include<cstdio>
#include<cmath>
int a[100][100];
void spt(int k){
    if(k==0)a[k+1][k+1]=k+1;
    else {
        spt(k-1);
        for(int i=(1<<(k-1))+1,t=i-1;i<=(1<<k);i++)
            for(int j=1;j<=1<<(k-1);j++){
                a[i][j]=a[i-t][j]+t;
                a[j][i]=a[i][j];
                a[i][j+t]=a[i-t][j];
            }
    }
}
int main(){
    int n,k;
    scanf("%d",&n);
    k=(int)log2(n);
    spt(k);
    for(int i=1;i<=(1<<k);i++){
        for(int j=2;j<=(1<<k);j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
    return 0;
}
/*
n=2^k;
input:
8
output:
2 3 4 5 6 7 8
1 4 3 6 5 8 7
4 1 2 7 8 5 6
3 2 1 8 7 6 5
6 7 8 1 2 3 4
5 8 7 2 1 4 3
8 5 6 3 4 1 2
7 6 5 4 3 2 1

*/
