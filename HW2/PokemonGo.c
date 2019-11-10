#include <stdio.h>
#define NDEBUG
#define MAXN 120

int det(int m, int n, int a[], int b[]){
	return (a[m] * b[n] - a[n] * b[m]);
}
void change(int m, int n, int a[], int b[]){
	int temp = a[m];
	a[m] = a[n];
	a[n] = temp;
	temp = b[m];
	b[m] = b[n];
	b[n] = temp;
	return;
}
int countdamage(int N, int a[], int b[], int check[]){
	int e = 0;
	int damage = 0;
	for (int i = 0; i < N; i++){
		if (check[i] != 0){
			damage += a[i] * e;
			e += b[i];
		}
	}
	return damage;
}
int main()
{
	int N, K;
	scanf("%d%d", &N, &K);
	int a[MAXN];
	int b[MAXN];
	int check[MAXN] = {0};
	for (int i = 0; i < N; i++)
		scanf("%d%d", &a[i], &b[i]);

	for (int i = N - 1; i > 0; i--){
		for (int j = 0; j < i; j++){
			if (det(j, j + 1, a, b) > 0)
				change(j, j + 1, a, b);
			if (det(j, j + 1, a, b) == 0){
				if (b[j] < b[j + 1])
					change(j, j + 1, a, b);
				else if (a[j] > a[j + 1])
					change(j, j + 1, a, b);
			}
		}
	}
	
#ifndef NDEBUG
	for (int i = 0; i < N; i++){
		printf("%d %d\n", a[i], b[i]);
	}
#endif

	int asum = 0;
	int bsum = 0;
	for (int i = N - 1; i >= N - K; i--){
		asum = asum + a[i];
		bsum = bsum + b[i];
		check[i] = 1;
	}

	for (int i = N - K - 1; i >= 0; i--){
		long long tempa = 0;
		long long tempb = bsum;
		int chindex = -1;
		long long maxdiff = 0;
		for (int j = N - 1; j > i; j--){
			if (check[j] != 0){
				tempb = tempb - b[j];
				long long difference = b[i] * (asum - a[j]) - tempb * a[j] - b[j] * tempa;
				if (difference >= maxdiff){
					maxdiff = difference;
					chindex = j;
				}
				tempa = tempa + a[j];
			}
		}
		if (chindex != -1){
			check[chindex] = 0;
			check[i] = 1;
			asum = asum - a[chindex] + a[i];
			bsum = bsum - b[chindex] + b[i];
		}
	}

	int damage = countdamage(N, a, b, check);
	
	printf("%d\n", damage);
	return 0;
}
