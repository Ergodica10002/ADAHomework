#include <iostream>
#include <algorithm>
#define MAXM 510000
#define MAXN 210000
#define NDEBUG
using namespace std;
typedef struct vertex{
	int v;
	unsigned long long l, d;
	struct vertex* nextv;
}vertex;

vertex* lists[MAXN];

typedef struct citem{
	int v;
	unsigned long long d;
}citem;

unsigned long long INF;
void makeinf(){
	INF = 1;
	for (int i = 0; i < 60; i++){
		INF = INF * 2;
	}
	return;
}
struct Compare {
    bool operator() (const citem &lhs, const citem &rhs) {
        return lhs.d > rhs.d;
    }
};
void initlists(int n){
	for (int i = 0; i < n; i++){
		lists[i] = NULL;
	}
	return;
}
unsigned long long max(unsigned long long a, unsigned long long b){
	return (a > b)? a : b;
}
void addedge(int a, int b, unsigned long long d, unsigned long long l){
	vertex* e = new vertex;
	e->v = b;
	e->l = l;
	e->d = d;
	e->nextv = NULL;
	vertex* current = lists[a];
	if (current == NULL)
		lists[a] = e;
	else{
		while (current->nextv != NULL)
			current = current->nextv;
		current->nextv = e;
	}
	return;
}
void printlist(int n){
	printf("printlist\n");
	for (int i = 0; i < n; i++){
		vertex* e = lists[i];
		while (e != NULL){
			printf("%d %d %lld %lld\n", i, e->v, e->d, e->l);
			e = e->nextv;
		}
	}
	return;
}

unsigned long long findminL(int n, int s, int t){
	unsigned long long d[MAXN];
	bool sure[MAXN] = {0};
	vector<citem> label;
	for (int i = 0; i < n; i++){
		d[i] = INF;
	}
	d[s] = 0;
	label.push_back((citem){s, (unsigned long long)d[s]});
	make_heap(label);
	sure[s] = 0;
	for (int i = 0; i < n; i++){
		if (sure[t] == 1)
			break;
//		while (!label.empty() && sure[label.top().v] == 1){
//			label.pop();
//		}
		int nowv = label[0];
		sure[nowv] = 1;
		label.pop();

		vertex* current = lists[nowv];
		while (current != NULL){
			int v = current->v;
			int l = current->l;
			if (sure[v] == 0 && d[v] > max(d[nowv], l)){
				d[v] = max(d[nowv], l);
				label.push((citem){v, d[v]});
			}
			current = current->nextv;
		}
	}
	return d[t];
}
void rmedge(int n, unsigned long long L){
	for (int i = 0; i < n; i++){
		vertex* current = lists[i];

		vertex* previous = lists[i];
		current = lists[i]->nextv;

		while (current != NULL){
			if (current->l > L){
				current = current->nextv;
				previous->nextv = current;
			}
			previous = previous->nextv;
			if (current != NULL)
				current = current->nextv;
		}

	}
	return;
}
unsigned long long findminD(int n, int s, int t, int L){
	unsigned long long d[MAXN];
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

//		while (!label.empty() && sure[nowa = label.top().v] == 1){
//			label.pop();
//		}

		int nowv = label.top().v;
		sure[nowv] = 1;
		label.pop();

		vertex* current = lists[nowv];
		while (current != NULL){
			int v = current->v;
			int ed = current->d;
			if (sure[v] == 0 && d[v] > d[nowv] + ed && current->l <= L){
				d[v] = d[nowv] + ed;
				label.push((citem){v, d[v]});
			}
			current = current->nextv;
		}
	}
	return d[t];
}
int main(){
	int n, m;
	int s, t;
	scanf("%d %d %d %d", &n, &m, &s, &t);
	initlists(n);
	for (int i = 0; i < m; i++){
		int a, b, d, l;
		scanf("%d %d %d %d", &a, &b, &d, &l);
		addedge(a, b, (unsigned long long)d, (unsigned long long)l);
		addedge(b, a, (unsigned long long)d, (unsigned long long)l);
	}
#ifndef NDEBUG
	printlist(n);
#endif
	makeinf();
	unsigned long long L = findminL(n, s, t);
	rmedge(n, L);
	unsigned long long D = findminD(n, s, t, L);
	if (s == t)
		printf("0 0\n");
	else
		printf("%llu %llu\n", D, L);


	return 0;
}