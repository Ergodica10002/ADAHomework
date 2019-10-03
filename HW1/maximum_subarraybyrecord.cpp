#include <stdio.h>
#define MAXN 600000
long long a[MAXN];
long long p[MAXN];
long long v[MAXN];
long long record[MAXN][50] = {{0}};
int power2table[MAXN];
long long max3(long long a, long long b, long long c){
	if (a >= b && a >= c)
		return a;
	else if (b >= a && b >= c)
		return b;
	return c;
}
int power2(long long n){
	if (n == 0)
		return 0;
	int c = 1;
	while (n / 2 != 0){
		c++;
		n /= 2;
	}
	return c;
}
void inittable(int n){
	long long powernum = 1;
	power2table[0] = 0;
	for (int i = 1; i < n; i++){
		if (i == powernum){
			power2table[i] = power2(i);
			powernum *= 2;
		}
		else
			power2table[i] = power2table[i - 1];
	}
	return;
}
long long maxsum(int left, int right, int pi){
	if ((pi - 1 < left || pi - 1 > right) && (pi != 0)){
		int interval = right - left;
		return record[left][power2table[interval]];
	}
	if (left == right){
		record[left][0] = a[left];
		return a[left];
	}
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
	long long result = max3((lmax + rmax), maxsum(left, mid, pi), maxsum(mid + 1, right, pi));
	int interval = right - left;
	record[left][power2table[interval]] = result;
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
	inittable(MAXN);
	long long toprint = maxsum(0, N - 1, 0);
	printf("%lld\n", (toprint > 0)? toprint : 0);
	for (int i = 0; i < Q; i++){
		a[p[i] - 1] = v[i];
		long long toprint = maxsum(0, N - 1, p[i]);
		printf("%lld\n", (toprint > 0)? toprint : 0);
	}

	return 0;
}

