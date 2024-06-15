#include<iostream>
#include<algorithm>
//修改内容2
using namespace std;
const int MAXN=1000005,p=998244353,g=3,invg=332748118;
int n=0,limit=1,l,r[MAXN]={};
long long b[MAXN]={},d[MAXN]={},F0[MAXN]={},G0[MAXN]={};
long long c[MAXN]={};//f[x]%(x^deg);
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
        B[i]=(2ll-c[i]*B[i]%p+p)%p*B[i]%p;
    }
    NTT(B,-1);
    fill(B+deg,B+limit,0);
}
void Mul(long long* A,int N,long long* B,int M,long long* ans)
{
    limit=1,l=0;
    while(limit<=N+M){
        limit<<=1;++l;
    }
    for(int i=0;i<limit;++i){
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    }
    NTT(A,1);
    NTT(B,1);
    for(int i=0;i<=limit;++i){
        ans[i]=A[i]*B[i]%p;
    }
    NTT(ans,-1);
}
void derivative(long long* A,long long* ans,int N)
{
    for(int i=1;i<N;++i){
        ans[i-1]=i*A[i]%p;
    }
    ans[N-1]=0;
}
void integrate(long long* A,long long* ans,int N)
{
    for(int i=1;i<N;++i){
        ans[i]=A[i-1]*quick_pow(i,p-2)%p;
    }
    ans[0]=0;
}
void Ln(long long* A,long long* ans,int N)
{
    for(int i=0;i<(N<<2);++i){
        b[i]=0,d[i]=0;
    }
    limit=1,l=0;
    derivative(A,d,N);
    get_inv(A,b,N);
    Mul(b,N,d,N,d);
    integrate(d,ans,N);
}
void Exp(long long* A,long long* B,int deg)//B(x)==e^(A[x]) (mod x^n)
{
    if(deg==1){
        B[0]=1;
        return;
    }
    Exp(A,B,(deg+1)>>1);
    limit=1,l=0;
    while(limit<=(deg<<1)){
        limit<<=1;++l;
    }
    for(int i=0;i<limit;++i){F0[i]=0;}
    Ln(B,F0,deg);
    for(int i=0;i<limit;++i){
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
        G0[i]=i<deg? A[i]:0;
    }
    NTT(G0,1);NTT(F0,1);NTT(B,1);
    for(int i=0;i<limit;++i){
        B[i]=((B[i]*(1ll-F0[i]+G0[i]))%p+p)%p;
    }
    NTT(B,-1);
    fill(B+deg,B+limit,0);
}
long long a1[MAXN]={},a2[MAXN]={};
inline int read()
{
	long long x=0;
	char c=getchar();
	while(c<'0' || c>'9'){c=getchar();}
	while(c>='0' && c<='9'){
		x=x*10+c-'0';
        x%=p;
		c=getchar();
	}
	return x;
}
int main()
{
    int k=0;
    n=read();
    k=read();
    for(int i=0;i<n;++i){
        a1[i]=read();
    }
    Ln(a1,a2,n);
    for(int i=0;i<n;++i){
        a2[i]=1ll*k*a2[i]%p;
    }
    Exp(a2,ans,n);
    for(int i=0;i<n;++i){
        cout<<ans[i]<<" ";
    }
    return 0;
}
