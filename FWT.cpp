#include<iostream>
using namespace std;
//修改内容1
typedef long long ll;
int n=0;
const int p=998244353;
const int inv_2=499122177;
const int MAXN=1000005;
ll a[MAXN]={},b[MAXN]={};
ll A[MAXN]={},B[MAXN]={},ans[MAXN]={};
void FWT_or(ll* f,int type)
{
    for(int mid=1;mid<n;mid<<=1){
	    for(int block=mid<<1,j=0;j<n;j+=block){
	        for(int i=j;i<j+mid;i++){
	            f[i+mid]=(f[i+mid]+f[i]*type+p)%p;
            }
        }
    }
}
void FWT_and(ll* f,int type)
{
    for(int mid=1;mid<n;mid<<=1){
	    for(int block=mid<<1,j=0;j<n;j+=block){
	        for(int i=j;i<j+mid;i++){
	            f[i]=(f[i]+f[i+mid]*type+p)%p;
            }
        }
    }
}
void FWT_xor(ll* f,int type)
{
    for(int mid=1;mid<n;mid<<=1){
	    for(int block=mid<<1,j=0;j<n;j+=block){
	        for(int i=j;i<j+mid;i++){
	            ll x=f[i],y=f[i+mid];
		        f[i]=(x+y)%p*(type==1?1:inv_2)%p;
		        f[i+mid]=(x-y+p)%p*(type==1?1:inv_2)%p;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    n=(1<<n);
    for(int i=0;i<n;++i){cin>>a[i];}
    for(int i=0;i<n;++i){cin>>b[i];}

    for(int i=0;i<n;++i){A[i]=a[i];}
    for(int i=0;i<n;++i){B[i]=b[i];}
    FWT_or(A,1);FWT_or(B,1);
    for(int i=0;i<n;++i){ans[i]=A[i]*B[i]%p;}
    FWT_or(ans,-1);
    for(int i=0;i<n;++i){cout<<ans[i]<<" ";}cout<<"\n";

    for(int i=0;i<n;++i){A[i]=a[i];}
    for(int i=0;i<n;++i){B[i]=b[i];}
    FWT_and(A,1);FWT_and(B,1);
    for(int i=0;i<n;++i){ans[i]=A[i]*B[i]%p;}
    FWT_and(ans,-1);
    for(int i=0;i<n;++i){cout<<ans[i]<<" ";}cout<<"\n";

    for(int i=0;i<n;++i){A[i]=a[i];}
    for(int i=0;i<n;++i){B[i]=b[i];}
    FWT_xor(A,1);FWT_xor(B,1);
    for(int i=0;i<n;++i){ans[i]=A[i]*B[i]%p;}
    FWT_xor(ans,-1);
    for(int i=0;i<n;++i){cout<<ans[i]<<" ";}cout<<"\n";

    return 0;
}
