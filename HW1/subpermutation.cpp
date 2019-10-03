#include <stdio.h>
#define MAXN 500000
int array[MAXN];
long long powertable[50];
int log2table[MAXN];
int maxtable[MAXN][30];
int mintable[MAXN][30];

int max2(int a, int b){
	return (a > b)? a : b;
}
int min2(int a, int b){
	return (a < b)? a : b;
}
int log2(long long a){
	int c = 0;
	while (a != 1){
		a /= 2;
		c++;
	}
	return c;
}
void initpowertable(int n){
	long long a = 1;
	for (int i = 0; i < n; i++){
		powertable[i] = a;
		a *= 2;
	}
	
	return;
}
void initlogtable(int n){
	log2table[0] = -1;
	log2table[1] = 0;
	int a = 2;
	int c = 0;
	for (int i = 1; i < n; i++){
		if (i == a){
			a = a * 2;
			c++;
		}
		log2table[i] = c;
	}
}
void buildmaxtable(int N){
	for (int i = 0; i < N; i++){
		maxtable[i][0] = array[i];
	}
	for (int j = 1; j < 30; j++){
		for (int i = 0; i + powertable[j] <= N; i++){
			maxtable[i][j] = max2(maxtable[i][j - 1], maxtable[i + powertable[j - 1]][j - 1]);
		}
	}
}
void buildmintable(int N){
	for (int i = 0; i < N; i++){
		mintable[i][0] = array[i];
	}
	for (int j = 1; j < 30; j++){
		for (int i = 0; i + powertable[j] <= N; i++){
			mintable[i][j] = min2(mintable[i][j - 1], mintable[i + powertable[j - 1]][j - 1]);
		}
	}
}
/*
long long findcount(int begin, int end){
	long long count = 0;
	count += findcount(begin, end - 1) + findcount(begin + 1, end);
	if ()
}*/
int main(void)
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &array[i]);
	initpowertable(30);
	initlogtable(N);
	buildmaxtable(N);
	buildmintable(N);
	long long count = N; 

	for (int i = 0; i < N; i++){
		for (int j = i + 1; j < N; j++){
			int interval = j - i;
			int c = log2table[interval];
			int max = max2(maxtable[i][c], maxtable[j - powertable[c] + 1][c]);
			int min = min2(mintable[i][c], mintable[j - powertable[c] + 1][c]);
		//	printf("i %d j %d max %d min %d\n", i, j, max, min);
			if ((max - min) == interval)
				count++;
		}
	}
	printf("%lld\n", count);
	return 0;
}

