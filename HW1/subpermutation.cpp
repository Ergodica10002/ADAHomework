#include <stdio.h>
#define MAXN 510000
#define NDEBUG
int array[MAXN];
int maxarr[2 * MAXN];
int minarr[2 * MAXN];
long long count = 0;
int countarr[2 * MAXN] = {0};
void buildleftarray(int left, int mid){
	minarr[mid] = maxarr[mid] = array[mid];
	for (int i = mid - 1; i >= left; i--){
		if (array[i] < minarr[i + 1])
			minarr[i] = array[i];
		else
			minarr[i] = minarr[i + 1];
		if (array[i] > maxarr[i + 1])
			maxarr[i] = array[i];
		else
			maxarr[i] = maxarr[i + 1];
	}
}
void buildrightarray(int right, int mid){
	minarr[mid + 1] = maxarr[mid + 1] = array[mid + 1];
	for (int i = mid + 2; i <= right; i++){
		if (array[i] < minarr[i - 1])
			minarr[i] = array[i];
		else
			minarr[i] = minarr[i - 1];
		if (array[i] > maxarr[i - 1])
			maxarr[i] = array[i];
		else
			maxarr[i] = maxarr[i - 1];
	}
}
void dp(int left, int right){
	if (left == right){
		count++;
		return;
	}
	if (left == right - 1){
		if (array[left] + 1 == array[right] || array[right] + 1 == array[left])
			count++;
		dp(left, left);
		dp(right, right);
		return;
	}
	int mid = (left + right) / 2;
	dp(left, mid);
	dp(mid + 1, right);
	buildleftarray(left, mid);
	buildrightarray(right, mid);
	
#ifndef NDEBUG
	printf("max:");
	for (int i = left; i <= right; i++)
		printf("%d ", maxarr[i]);
	printf("\nmin:");
	for (int i = left; i <= right; i++)
		printf("%d ", minarr[i]);
	printf("\n");
#endif
//left large left small
	long long segcount = 0;
	for (int i = mid; i >= left; i--){
		int x = maxarr[i] - minarr[i];
		if (x + i > mid && x + i <= right){
			if (maxarr[x + i] < maxarr[i] && minarr[x + i] > minarr[i]){
				segcount++;
			}
		}
	}
	count += segcount;
//right large right small
	segcount = 0;
	for (int i = mid + 1; i <= right; i++){
		int x = maxarr[i] - minarr[i];
		if (i - x <= mid && i - x >= left){
			if (maxarr[i - x] < maxarr[i] && minarr[i - x] > minarr[i]){
				segcount++;
			}
		}
	}
	count += segcount;
//left large right small
	segcount = 0;
	int maxp = mid + 1, minp = mid + 1;
	for (int i = mid; i >= left; i--){
		while (maxp <= right && maxarr[maxp] < maxarr[i]){
			countarr[minarr[maxp] + maxp]++;
			maxp++;
		}
		while (minp <= right && minarr[minp] > minarr[i]){
			countarr[minarr[minp] + minp]--;
			minp++;
		}
		int value = maxarr[i] + i;
		if (countarr[value] >= 0)
			segcount += countarr[value];
	}
	count += segcount;
	for (int i = mid + 1; i <= right; i++){
		countarr[minarr[i] + i] = 0;
	}
	for (int i = mid; i >= left; i--){
		countarr[MAXN - (minarr[i] - i)] = 0;
	}
	
//right large left small
	segcount = 0;
	maxp = mid, minp = mid;
	for (int i = mid + 1; i <= right; i++){
		while (maxp >= left && maxarr[maxp] < maxarr[i]){
			countarr[MAXN - (minarr[maxp] - maxp)]++;
			maxp--;
		}
		while (minp >= left && minarr[minp] > minarr[i]){
			countarr[MAXN - (minarr[minp] - minp)]--;
			minp--;
		}
		int value = maxarr[i] - i;
		if (countarr[MAXN - value] >= 0){
			segcount += countarr[MAXN - value];
		}
	}
	count += segcount;
	for (int i = mid + 1; i <= right; i++){
		countarr[minarr[i] + i] = 0;
	}
	for (int i = mid; i >= left; i--){
		countarr[MAXN - (minarr[i] - i)] = 0;
	}
	
	return;
}
int main(void)
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &array[i]);
	dp(0, N - 1);

	printf("%lld\n", count);
	return 0;
}

