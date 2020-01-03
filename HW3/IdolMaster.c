#include <stdio.h>
#define MAXN 300000
#define NDEBUG
typedef struct{
	int outv;
	int indeg;
	int contain;
}vertex;
vertex vlist[MAXN];
int indegtable[MAXN];
int deletelist[MAXN] = {0};
int tempdelnum;
void initlist(int N){
	for (int i = 0; i <= N; i++){
		vlist[i].indeg = 0;
		vlist[i].contain = 1;
	}
	return;
}
void inittable(int N){
	for (int i = 0; i <= N; i++){
		indegtable[i] = vlist[i].indeg;
	}
	return;
}
void printlist(int N){
	printf("printlist\n");
	for (int i = 1; i <= N; i++){
		printf("%d %d %d\n", i, vlist[i].outv, vlist[i].indeg);
	}
}
void resumetable(){
	for (int i = 0; i < tempdelnum; i++){
		indegtable[vlist[deletelist[i]].outv] = vlist[vlist[deletelist[i]].outv].indeg;
	}
	return;
}
int todelete(int deletev){
	int deletetotal = 0;
//path_compression
	int nowchild = deletev;
	if (vlist[deletev].outv == 0)
		return 1;
	while (vlist[nowchild].outv != 0 && vlist[vlist[nowchild].outv].indeg == 1){
		int newparent = vlist[vlist[nowchild].outv].outv;
		vlist[deletev].outv = newparent;
		vlist[deletev].contain++;
	}
	if (vlist[vlist[deletev].outv].outv == 0){
		vlist[deletev].outv = 0;
		vlist[deletev].contain++;
	}
	deletetotal += vlist[deletev].contain;
	if (vlist[deletev].outv == 0)
		return deletetotal;

	indegtable[vlist[deletev].outv]--;
	deletelist[tempdelnum] = deletev;
	tempdelnum++;
	if (indegtable[vlist[deletev].outv] == 0){
		nowchild = vlist[deletev].outv;
		while (vlist[nowchild].outv != 0 && indegtable[nowchild] == 0){
			indegtable[vlist[nowchild].outv]--;
			deletelist[tempdelnum] = nowchild;
			tempdelnum++;
			deletetotal++;
			nowchild = vlist[nowchild].outv;
		}
	}

	return deletetotal;

}
int main(){
	int N;
	scanf("%d", &N);
	initlist(N);
	for (int i = 1; i <= N; i++){
		int pi;
		scanf("%d", &pi);
		vlist[i].outv = pi;
		vlist[pi].indeg++;
	}
	inittable(N);
#ifndef NDEBUG
	printlist(N);
#endif
	int Q;
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++){
		int deletenum;
		int deletetotal = 0;
		tempdelnum = 0;
		scanf("%d", &deletenum);
		for (int j = 0; j < deletenum; j++){
			int deletev;
			scanf("%d", &deletev);
			deletetotal += todelete(deletev);
		}
		printf("%d\n", deletetotal);
		resumetable();
#ifndef NDEBUG
		for (int i = 0; i <= N; i++)
			printf("indegtable %d %d\n", i, indegtable[i]);

#endif		
	}

}