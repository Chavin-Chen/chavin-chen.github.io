#include<iostream>
using namespace std;
int a[20];
int main(){
    int n;
    long long ans;
    while(cin>>n){
        ans=-1;
        for(int i=0;i<n;i++)
            cin>>a[i];
        for(int i=0;i<n;i++){
            long long maxn=a[i];
            for(int j=i+1;j<n;j++){
                maxn*=a[j];
                ans=(maxn>ans)?maxn:ans;
            }
        }
        cout<<((ans>0)?ans:-1)<<endl;
    }
    return 0;
}
/*
input:
3
2 4 -3
5
2 5 -1 2 -1
5
2 5 -1 2 -5
5
-1 0 1 -2 2
5
-1 -2 3 2 -1
output:
8
20
100
-1
12

*/
