#include <stdio.h>
#define MAXN 200000
#define INFINITY 2147483640
#define NDEBUG

int notes[MAXN];
int effort[MAXN];
int dptable[MAXN];
int abs(int a){
	return (a < 0)? -a : a;
}
int movecost(int note1, int note2, int K);
void filleffort(int N, int K){		//effort made by one hand move from note1 to note2
	effort[0] = 0;
	for (int i = 1; i < N; i++)
		effort[i] = effort[i - 1] + movecost(i - 1, i, K);
	return;
}
int movecost(int note1, int note2, int K){		//one hand move from note1 to note2
	if (note1 >= note2)							//note1 + 1 to note2 - 1 is made by the other hand
		return 0;
	int extrak = (note2 - note1) * K;							
	if (abs(notes[note1] - notes[note2]) > extrak)
		return abs(notes[note1] - notes[note2]) - extrak;
	else
		return 0;
}
int counteffort(int N, int M, int K){
	dptable[0] = 0;
	dptable[1] = 0;
	const int L = M; 
	for (int i = 2; i < N; i++){
		if (i <= L){
			int min = INFINITY;
			for (int j = 1; j < i; j++){
				int cost = dptable[j] + (effort[i - 1] - effort[j]) + movecost(j - 1, i, K);
				if (min > cost)
					min = cost;
			}
			int cost = effort[i - 1];
			if (min > cost)
				min = cost;
			dptable[i] = min;
		}
		else{
			int min = INFINITY;
			for (int j = i - L; j < i; j++){
				int cost = dptable[j] + (effort[i - 1] - effort[j]) + movecost(j - 1, i, K);
				if (min > cost)
					min = cost;
			}
			dptable[i] = min;
		}
	}
#ifndef NDEBUG		//printtable
	printf("dp:\n");
	for (int i = 0; i < N; i++){
		printf("%d ", dptable[i]);
	}
	printf("\n");
#endif
	int result = INFINITY;
	for (int i = N - L; i < N; i++){
		int cost = dptable[i] + effort[N - 1] - effort[i];
		if (result > cost)
			result = cost;
	}
	return result;
}

int main(){
	int N, M, K;
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 0; i < N; i++)
		scanf("%d", &notes[i]);
	filleffort(N, K);
#ifndef NDEBUG
	for (int i = 0; i < N; i++)
		printf("%d ", notes[i]);
	printf("\n");
#endif
	printf("%d\n", counteffort(N, M, K));
}