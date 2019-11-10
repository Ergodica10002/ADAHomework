#include <stdio.h>
#define MAXN 120
#define MAXV 110
#define NDEBUG
int a[MAXN];
int b[MAXN];
int check[MAXN] = {0};
int DP[MAXN][3][MAXN * MAXV] = {{{0}}};

int det(int m, int n){
	return (a[m] * b[n] - a[n] * b[m]);
}
void change(int m, int n){
	int temp = a[m];
	a[m] = a[n];
	a[n] = temp;
	temp = b[m];
	b[m] = b[n];
	b[n] = temp;
	return;
}
void inittable(int N, int K){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < MAXN * MAXV; j++){
			DP[i][K % 2][j] = -1;
		}
	}
	if (K == 1){
		for (int i = 0; i < N; i++){
			DP[i][1][b[i]] = 0;
		}
	}
	return;
}
void fillDP(int m, int n){

	for (int i = 0; i < m; i++){
		for (int j = 0; j <= (n - 1) * MAXV; j++){
			if (DP[i][(n - 1) % 2][j] != -1){
				if (DP[i][(n - 1) % 2][j] + a[m] * j > DP[m][n % 2][j + b[m]]){
					DP[m][n % 2][j + b[m]] = DP[i][(n - 1) % 2][j] + a[m] * j;
				}
			}
		}
	}
	
}
void printDP(int N, int K){
	printf("printDP\n");
	for (int i = 0; i < N; i++){
		for (int j = 0; j < MAXV * K; j++){
			if (DP[i][K % 2][j] != -1)
				printf("i %d sum %d damage %d\n", i, j, DP[i][K % 2][j]);
		}
	}
}
int main()
{
	int N, K;
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; i++)
		scanf("%d%d", &a[i], &b[i]);
	for (int i = N - 1; i > 0; i--){
		for (int j = 0; j < i; j++){
			if (det(j, j + 1) > 0)
				change(j, j + 1);
			if (det(j, j + 1) == 0){
				if (b[j] < b[j + 1])
					change(j, j + 1);
				else if (a[j] > a[j + 1])
					change(j, j + 1);
			}
		}
	}
#ifndef NDEBUG
	for (int i = 0; i < N; i++){
		printf("%d %d\n", a[i], b[i]);
	}
#endif
	inittable(N, 1);
	for (int i = 2; i <= K; i++){
		inittable(N, i);
		for (int j = i - 1; j < N - K + i; j++){
			fillDP(j, i);
		}
	}
#ifndef NDEBUG
	printDP(N, K);
#endif
	int maxdamage = 0;
	for (int i = K - 1; i < N; i++){
		for (int j = b[i]; j < K * MAXV; j++){
			if (DP[i][K % 2][j] > maxdamage)
				maxdamage = DP[i][K % 2][j];
		}
		
	}
	printf("%d\n", (K == 1)? 0 : maxdamage);
	return 0;
}
