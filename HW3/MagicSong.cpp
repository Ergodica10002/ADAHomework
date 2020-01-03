#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 11000
#define MAXM 51000
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NDEBUG
using namespace std;
int slength[MAXN];
unsigned long long dp[2 * MAXN + MAXM] = {0};
int color[2 * MAXN + MAXM] = {WHITE};
int jumpsong[MAXN] = {0};


inline int Read(){
	char c;
	int answer = 0;
	while(!isdigit(c = getchar()));
	do {
		answer = (answer << 3) + (answer << 1) + c - '0';
	}while(isdigit(c = getchar()));
	return answer;
}
void initarray(int N, int M){
	for (int i = 0; i < 2 * N + M + 10; i++){
		color[i] = 0;
		dp[i] = 0;
	}
	for (int i = 0; i < N + 10; i++)
		jumpsong[i] = 0;
	return;
}

unsigned long long max(unsigned long long a, unsigned long long b){
	return (a > b)? a : b;
}
typedef struct vertex{
	int index;
	unsigned long long length;
}vertex;

vector <vertex> vlist[MAXN];

typedef struct jump{
	int s1, t1, s2, t2;
}jump;

vector <jump> jumplist;

bool Compare (const jump &lhs, const jump &rhs) {
    if (lhs.s1 < rhs.s1)
    	return 1;
    else if (lhs.s1 > rhs.s1)
    	return 0;
    else{
    	if (lhs.t1 < rhs.t1)
    		return 1;
    	else
    		return 0;
    }
}

void addendNODE(int index){
	vlist[2 * index - 1].push_back((vertex){2 * index, (unsigned long long)slength[index]});
}

void buildgraph(int N){
	int mididx = 0;
	int jumpsize = jumplist.size();

	while (mididx < jumpsize){
		int head = jumplist[mididx].s1;
		vlist[2 * head - 1].push_back((vertex){2 * N + mididx + 1, (unsigned long long)jumplist[mididx].t1 + 1});
		mididx++;
	}
	
	for (int i = 0; i < jumpsize; i++){
		int s1 = jumplist[i].s1;
		int t1 = jumplist[i].t1;
		int s2 = jumplist[i].s2;
		int t2 = jumplist[i].t2;
		vlist[2 * N + i + 1].push_back((vertex){2 * s2, (unsigned long long)slength[s2] - t2});
	}
	int jumpidx = 0;
	jumpsong[jumplist[jumpidx].s1] = jumpidx;
	jumpidx++;
	while (jumpidx < jumpsize){
		if (jumplist[jumpidx].s1 != jumplist[jumpidx - 1].s1){
			int s1 = jumplist[jumpidx].s1;
			jumpsong[s1] = jumpidx;
		}
		jumpidx++;
	}
	for (int i = 0; i < jumpsize; i++){

		int start = jumpsong[jumplist[i].s2];

		while (start < jumpsize && jumplist[start].s1 == jumplist[i].s2){
			if (jumplist[start].t1 > jumplist[i].t2){
				int tlength = jumplist[start].t1 - jumplist[i].t2 + 1;
				vlist[2 * N + i + 1].push_back((vertex){2 * N + start + 1, (unsigned long long)tlength});
			}
			start++;
		}
		
	}
	return;
}

void printgraph(int N, int M){
	for (int i = 1; i <= 2 * N + M; i++){
		for (int j = 0; j < vlist[i].size(); j++)
			printf("%d %d %d\n", i, vlist[i][j].index, vlist[i][j].length);
	}
	return;
}

void DFS(int N, int startidx, bool &iscycle){
	if (startidx <= 2 * N && startidx % 2 == 0){
		return;
	}
	color[startidx] = GRAY;
	int adjnum = vlist[startidx].size();

	for (int i = 0; i < adjnum; i++){
		if (color[vlist[startidx][i].index] == GRAY){
			iscycle = 1;
			break;
		}
		if (color[vlist[startidx][i].index] == WHITE){
			DFS(N, vlist[startidx][i].index, iscycle);
		}
		unsigned long long temp = dp[vlist[startidx][i].index];
		dp[startidx] = max(dp[startidx], temp + vlist[startidx][i].length); 
	}

	color[startidx] = BLACK;
	return;
}

int main(){
	int T;
	T = Read();
	int N, M;
	for (int i = 0; i < T; i++){
		N = Read();
		M = Read();
		initarray(N, M);
		for (int j = 1; j <= N; j++)
			slength[j] = Read();
		for (int j = 1; j <= N; j++){
			addendNODE(j);
		}

		for (int j = 1; j <= M; j++){
			int s1, s2, t1, t2;
			s1 = Read();
			t1 = Read();
			s2 = Read();
			t2 = Read();
			jumplist.push_back((jump){s1, t1, s2, t2});
		}
		sort(jumplist.begin(), jumplist.end(), Compare);
#ifndef NDEBUG
		for (int j = 0; j < M; j++){
			printf("j %d %d %d %d\n", jumplist[j].s1, jumplist[j].t1, jumplist[j].s2, jumplist[j].t2);
		} 
#endif
		buildgraph(N);
#ifndef NDEBUG
		printgraph(N, M);
#endif
		bool iscycle = 0;
		for (int j = 1; j <= N; j++){
			if (color[2 * j - 1] == BLACK){
				continue;
			}
			DFS(N, 2 * j - 1, iscycle);
			if (iscycle == 1){
				printf("LoveLive!\n");
				break;
			}
			dp[0] = max(dp[0], dp[2 * j - 1]);
		}
		if (!iscycle)
			printf("%llu\n", dp[0]);

	}


	return 0;
}