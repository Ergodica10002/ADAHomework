#include <stdio.h>
#define MAXN 600
long long a[MAXN];
long long p[MAXN];
long long v[MAXN];
long long record[MAXN][MAXN] = {{0}};
long long max3(long long a, long long b, long long c){
	if (a >= b && a >= c)
		return a;
	else if (b >= a && b >= c)
		return b;
	return c;
}
long long maxsum(int left, int right, int pi){
//	if ((pi < left || pi > right) && (record[left][right] != 0))
//		return record[left][right];
	if (left == right)
		return a[left];
	int mid = left + (right - left) / 2;
	long long sum = 0;
	long long lmax = a[mid];
	for (int i = mid; i >= left; i--){
		sum = sum + a[i];
		if (sum > lmax)
			lmax = sum;
	}
	sum = 0;
	long long rmax = a[mid + 1];
	for (int i = mid + 1; i <= right; i++){
		sum = sum + a[i];
		if (sum > rmax)
			rmax = sum;
	}
	int result = max3((lmax + rmax), maxsum(left, mid, pi), maxsum(mid + 1, right, pi));
	record[left][right] = result;
	return result;
}
int main(void)
{
	int N, Q;
	scanf("%d%d", &N, &Q);
	for (int i = 0; i < N; i++)
		scanf("%lld", &a[i]);
	for (int i = 0; i < Q; i++)
		scanf("%lld %lld", &p[i], &v[i]);
	long long toprint = maxsum(0, N - 1, 0);
	printf("%lld\n", (toprint > 0)? toprint : 0);
	for (int i = 0; i < Q; i++){
		a[p[i] - 1] = v[i];
		long long toprint = maxsum(0, N - 1, p[i]);
		printf("%lld\n", (toprint > 0)? toprint : 0);
	}

	return 0;
}

