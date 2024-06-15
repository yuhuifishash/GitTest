#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=300005,p=998244353,g=3,invg=332748118;
int N=0,limit=1,l,r[MAXN]={};
long long a[MAXN]={},b[MAXN]={};
long long c[MAXN]={};//f[x]%(x^deg);
long long F0[MAXN]={},G0[MAXN]={};
long long ans[MAXN]={};
long long quick_pow(long long a,long long b)
{
    long long ans=1;
    while(b){
        if(b&1){
            ans=ans*a%p;
        }
        a=a*a%p;
        b>>=1;
    }
    return ans%p;
}
void NTT(long long* A,int type)
{
    for(int i=0;i<limit;++i){
        if(i<r[i]){swap(A[i],A[r[i]]);}
    }
    for(int mid=1;mid<limit;mid<<=1){
        long long Wn=quick_pow(type==1?g:invg , (p-1)/(mid<<1));
        for(int j=0;j<limit;j+=(mid<<1)){
            long long w=1;
            for(int k=0;k<mid;++k,w=(w*Wn)%p){
                int x=A[j+k], y=w*A[j+k+mid]%p;
                A[j+k]=(x+y)%p;
                A[j+k+mid]=(1ll*x-y+p)%p;
            }
        }
    }
    if(type==1){return;}
    long long inv=quick_pow(limit,p-2);
    for(int i=0;i<limit;++i){
        A[i]=A[i]*inv%p;
    }
}
void get_inv(long long* A,long long* B,int deg)//B为A逆元
{
    if(deg==1){
        B[0]=quick_pow(A[0],p-2);
        return;
    }
    get_inv(A,B,(deg+1)>>1);
    limit=1,l=0;
    while(limit<=(deg<<1)){
        limit<<=1;++l;
    }
    for(int i=0;i<limit;++i){
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
        c[i]=i<deg? A[i]:0;
    }
    NTT(c,1);NTT(B,1);
    for(int i=0;i<limit;++i){
        B[i]=(2ll-c[i]*B[i]+p)%p*B[i]%p;
    }
    NTT(B,-1);
    fill(B+deg,B+limit,0);
}
long long inv2=0;
void Sqrt(long long* A,long long* B,int deg)
{
    if(deg==1){
        B[0]=1;
        return;
    }
    Sqrt(A,B,(deg+1)>>1);
    limit=1,l=0;
    while(limit<=(deg<<1)){
        limit<<=1;++l;
    }
    for(int i=0;i<limit;++i){F0[i]=0;}
    get_inv(B,F0,deg);
    for(int i=0;i<limit;++i){
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
        G0[i]=i<deg? A[i]:0;
    }
    NTT(G0,1);NTT(F0,1);NTT(B,1);
    for(int i=0;i<limit;++i){
        B[i]=F0[i]*(G0[i]+B[i]*B[i]%p)%p*inv2%p;
    }
    NTT(B,-1);
    fill(B+deg,B+limit,0);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    inv2=quick_pow(2,p-2);
    cin>>N;
    for(int i=0;i<N;++i){
        cin>>a[i];
    }
    Sqrt(a,ans,N);
    for(int i=0;i<N;++i){
        cout<<ans[i]<<" ";
    }
    return 0;
}