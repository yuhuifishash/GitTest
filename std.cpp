#include<bits/stdc++.h>
#define int long long
#define MK 100010
using namespace std;
int n,m;
int S,T;
int dep[MK];
int ans;
int tot = 0;

struct node
{
	int next,to,v;
}e[MK*2];

int ei = 1,h[MK];

void add(int x,int y,int v)
{
	ei++;
	e[ei].to = y;
	e[ei].v = v;
	e[ei].next = h[x];
	h[x] = ei;
}

int bfs()
{
	queue<int>qu;
	memset(dep,0,sizeof(dep));
	dep[S] = 1;
	qu.push(S);
	while(!qu.empty())
	{
		int f1 = qu.front();
		qu.pop();
		for(int i=h[f1];i;i=e[i].next)
		{
			int to = e[i].to;
			if(dep[to]!=0 || e[i].v==0)
			{
				continue;
			}
			qu.push(to);
			dep[to] = dep[f1]+1;
		}
	}
	return dep[T]!=0;
}

int dfs(int from,int maxflow)
{
	if(from==T)
	{
		return maxflow;
	}
	int flow = 0;
	for(int i=h[from];i;i=e[i].next)
	{
		int to = e[i].to;
		if(dep[to]!=dep[from]+1 || e[i].v==0)
		{
			continue;
		}
		int rst = dfs(to,min(maxflow-flow,e[i].v));
		if(rst==0)
		{
			dep[to] = 0;
		}
		e[i].v -= rst;
		e[i^1].v += rst;
		flow += rst;
		if(flow==maxflow)
		{
			break;
		}
	}
	return flow;
}

void dinic()
{
	while(bfs())
	{
		ans += dfs(S,LLONG_MAX);
	}
}

signed main()
{
	scanf("%lld%lld",&n,&m);
	while(1)
	{
		int x,y;
		scanf("%lld%lld",&x,&y);
		if(x==-1 && y==-1)
		{
			break;
		}
		add(x,y,1);
		add(y,x,0);
	}
	S = 1000;
	T = 1001;
	for(int i=1;i<=n;i++)
	{
		add(S,i,1);
		add(i,S,0);
	}
	for(int i=n+1;i<=m;i++)
	{
		add(i,T,1);
		add(T,i,0);
	}
	dinic();
	if(ans==0)
	{
		printf("No Solution\n");
		return 0;
	}else
	{
		printf("%lld\n",ans);
		for(int i=2;i<=ei;i=i+2)
		{
			if(e[i].to!=S && e[i].to!=T && e[i^1].to!=S && e[i^1].to!=T && e[i^1].v!=0)
			{
				printf("%lld %lld\n",e[i].to,e[i^1].to);
			}
		}
	}
	return 0;
}