#include<bits/stdc++.h>
using namespace std;

#define WA 2
#define AC 0

const int N = 1e5 + 5;
int G[205][205] = {};
int vis[205] = {};

int main(int cmdline_num, char * cmdline[])
	/*
	 * cmdline[1] = 1.in;  //input
	 * cmdline[2] = 1.out; //output
	 * cmdline[3] = 1.exp; //answer
	 */
{
	char inputfile[256], outputfile[256], stdoutfile[256];
	sprintf(inputfile, "%s", cmdline[1]);
    sprintf(stdoutfile, "%s", cmdline[2]);              
	sprintf(outputfile, "%s", cmdline[3]);            

	FILE *fin = fopen(inputfile, "r");
	FILE *fout = fopen(outputfile, "r");
    FILE *fstdout = fopen(stdoutfile, "r");

	int n, m, ans;
	fscanf(fin, "%d", &m);
    fscanf(fin, "%d", &n);
    fscanf(fstdout, "%d", &ans);

    while(1){
        int u = 0,v = 0;
        fscanf(fin, "%d", &u);
        fscanf(fin, "%d", &v);
        if(u == -1 && v == -1){break;}
        G[u][v] = 1;
    }
    
    int max_num = 0;
    if(fscanf(fout, "%d", &max_num) != 1) return WA;

    if(max_num != ans){
        return WA;
    }
    memset(vis,0,sizeof(vis));
    for(int i = 1; i <= max_num; ++i){
        int u = 0, v = 0;
        if(fscanf(fout, "%d", &u) != 1) return WA;
        if(fscanf(fout, "%d", &v) != 1) return WA;

        if(u <= 0 || u > m) return WA;
        if(v <= m || v > n) return WA;

        if(G[u][v] != 1){return WA;}
        if(vis[u] == 1){return WA;}
        if(vis[v] == 1){return WA;}
        vis[u] = 1;
        vis[v] = 1;
    }

	// 后面一段判断 是否有多余的输出
	while (1) {
		char ch = fgetc(fout);
		if (ch == ' ' || ch == '\n' || ch == '\r') ;
		else if (ch == EOF) break;
		else return WA;
	}
	int start = ftell(fout);
	fseek(fout, 0, SEEK_END);
	int end = ftell(fout);
	if (start < end) return WA;
	// -------------------------------


	
	// cout << "AC\n";
	return AC;
}