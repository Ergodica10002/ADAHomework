#include <stdio.h>
#define MAXN 300000
typedef struct{
	int vidx;
	int outv;
	int indeg;
}vertex;
vertex vlist[MAXN];
void initlist(int N){
	for (int i = 0; i < N; i++){
		vlist[i].vidx = i;
		vlist[i].indeg = 0;
	}
	return;
}
void printlist(int N){
	printf("printlist\n");
	for (int i = 0; i < N; i++){
		printf("%d %d %d\n", vlist[i].vidx, vlist[i].outv, vlist[indeg]);
	}
}
int main(){
	int N;
	scanf("%d", &N);
	initlist(N);
	for (int i = 0; i < N; i++){
		int pi;
		scanf("%d", &pi);
		vlist[i].outv = pi;
		vlist[pi].indeg++;
	}
#ifndef NDEBUG
	printlist(N);
#endif

}