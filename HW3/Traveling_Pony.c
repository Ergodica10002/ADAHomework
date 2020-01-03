#include <stdio.h>
#include <stdlib.h>
#define MAXM 510000
#define MAXN 210000
#define INF 2147483640
#define NDEBUG
typedef struct vertex{
	int a;
	int l, d;
	struct vertex* nextv;
}vertex;
vertex* lists[MAXN];
void initlists(int n){
	for (int i = 0; i < n; i++){
		lists[i] = NULL;
	}
	return;
}
int max(int a, int b){
	return (a > b)? a : b;
}
void addedge(int a, int b, int d, int l){
	vertex* e = (vertex*)malloc(sizeof(vertex));
	e->a = b;
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
	printf("now\n");
	for (int i = 0; i < n; i++){
		vertex* e = lists[i];
		while (e != NULL){
			printf("%d %d %d %d\n", i, e->a, e->d, e->l);
			e = e->nextv;
		}
	}
	return;
}
int findminL(int n, int s, int t){
	int d[MAXN];
	int sure[MAXN] = {0};
	for (int i = 0; i < n; i++){
		if (i == s)
			d[i] = 0;
		else
			d[i] = INF;
	}
	for (int i = 0; i < n; i++){
		if (sure[t] == 1)
			break;
		int nowa, min;
		min = INF;
		for (int j = 0; j < n; j++){
			if (d[j] < min && sure[j] == 0){
				nowa = j;
				min = d[j];
			}
		}
		d[nowa] = min;
		sure[nowa] = 1;

		vertex* current = lists[nowa];
		while (current != NULL){
			if (d[current->a] > max(d[nowa], current->l))
				d[current->a] = max(d[nowa], current->l);
			current = current->nextv;
		}
	}
	return d[t];
}
int findminD(int n, int s, int t, int L){
	int d[MAXN];
	int sure[MAXN] = {0};
	for (int i = 0; i < n; i++){
		if (i == s)
			d[i] = 0;
		else
			d[i] = INF;
	}
	for (int i = 0; i < n; i++){
		if (sure[t] == 1)
			break;
		int nowa, min;
		min = INF;
		for (int j = 0; j < n; j++){
			if (d[j] < min && sure[j] == 0){
				nowa = j;
				min = d[j];
			}
		}
		d[nowa] = min;
		sure[nowa] = 1;

		vertex* current = lists[nowa];
		while (current != NULL){
			if (d[current->a] > d[nowa] + current->d && current->l <= L)
				d[current->a] = d[nowa] + current->d;
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
		addedge(a, b, d, l);
		addedge(b, a, d, l);
	}
#ifndef NDEBUG
	printlist(n);
#endif
	int L = findminL(n, s, t);
	int D = findminD(n, s, t, L);
	if (s == t)
		printf("0 0\n");
	else
		printf("%d %d\n", D, L);


	return 0;
}