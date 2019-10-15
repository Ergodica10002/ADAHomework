#include <stdio.h>
#define MAXN 600000
long long a[MAXN];
long long p[MAXN];
long long v[MAXN];
long long maxsum(int N){
	long long sum = 0, max = a[0];
	for (int i = 0; i < N; i++){
		sum = sum + a[i];
		if (sum < 0)
			sum = 0;
		if (sum > max)
			max = sum;
	}
	if (max > 0)
		return max;
	return 0;
}
int main(void)
{
	int N, Q;
	scanf("%d %d", &N, &Q);
	for (int i = 0; i < N; i++)
		scanf("%lld", &a[i]);
	for (int i = 0; i < Q; i++)
		scanf("%lld %lld", &p[i], &v[i]);
	printf("%lld\n", maxsum(N));
	for (int i = 0; i < Q; i++){
		a[p[i] - 1] = v[i];
		printf("%lld\n", maxsum(N));
	}

	return 0;
}

