#include <iostream>
#include <vector>
#include <queue>
#define MAXM 510000
#define MAXN 210000
#define INF (unsigned long long) 1 << 60
#define NDEBUG
using namespace std;

typedef struct vertex{
	int v;
	unsigned long long d;
	unsigned long long l;
}vertex;

vector<vertex> lists[MAXN];

unsigned long long d[MAXN];
typedef struct citem{
	int v;
	unsigned long long d;
}citem;

struct Compare {
    bool operator() (const citem &lhs, const citem &rhs) {
        return lhs.d > rhs.d;
    }
};

unsigned long long max(unsigned long long a, unsigned long long b){
	return (a > b)? a : b;
}
void addedge(int a, int b, unsigned long long d, unsigned long long l){
	vertex v1, v2;
	
	lists[a].push_back((vertex){b, d, l});
	lists[b].push_back((vertex){a, d, l});
	return;
}
void printlist(int n){
	printf("printlist\n");
	for (int i = 0; i < n; i++){
		for (vertex v : lists[i]){
			printf("%d %d %d %d\n", i, v.v, v.d, v.l);
		}
	}
	return;
}

unsigned long long findminL(int n, int s, int t){
	bool sure[MAXN] = {0};
	priority_queue<citem, vector<citem>, Compare> label;
	for (int i = 0; i < n; i++){
		d[i] = INF;
	}
	d[s] = 0;
	label.push((citem){s, (unsigned long long)d[s]});
	sure[s] = 0;
	for (int i = 0; i < n; i++){
		if (sure[t] == 1)
			break;
//		while (!label.empty() && sure[label.top().v] == 1){
//			label.pop();
//		}
		int nowv = label.top().v;
		sure[nowv] = 1;
		label.pop();

		for (vertex v : lists[nowv]){
			if (sure[v.v] == 0 && d[v.v] > max(d[nowv], v.l)){
				d[v.v] = max(d[nowv], v.l);
				label.push((citem){v.v, d[v.v]});
			}
		}
	}
	return d[t];
}

unsigned long long findminD(int n, int s, int t, int L){
	bool sure[MAXN] = {0};
	priority_queue<citem, vector<citem>, Compare> label;
	for (int i = 0; i < n; i++){
		d[i] = INF;
	}
	d[s] = 0;
	label.push((citem){s, (unsigned long long)d[s]});
	sure[s] = 0;
	for (int i = 0; i < n; i++){
		if (sure[t] == 1)
			break;

		int nowv = label.top().v;
		sure[nowv] = 1;
		label.pop();

		for (vertex v : lists[nowv]){
			if (sure[v.v] == 0 && d[v.v] > d[nowv] + v.d && v.l <= L){
				d[v.v] = d[nowv] + v.d;
				label.push((citem){v.v, d[v.v]});
			}
		}
	}
	return d[t];
}
int main(){
	int n, m;
	int s, t;
	scanf("%d %d %d %d", &n, &m, &s, &t);
	for (int i = 0; i < m; i++){
		int a, b, d, l;
		scanf("%d %d %d %d", &a, &b, &d, &l);
		addedge(a, b, (unsigned long long)d, (unsigned long long)l);
	}
#ifndef NDEBUG
	printlist(n);
#endif
	unsigned long long L = findminL(n, s, t);

	unsigned long long D = findminD(n, s, t, L);
	if (s == t)
		printf("0 0\n");
	else
		printf("%llu %llu\n", D, L);


	return 0;
}