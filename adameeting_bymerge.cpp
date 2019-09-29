#include <iostream>
#include <vector>
#define MAXN 5000000
#define INFINITY 2147483600
#define NDEBUG
using namespace std;
int p[MAXN];
int f[MAXN];
int array[MAXN];
long long merge(int N, int now){
#ifndef NDEBUG
	int s = 0;
	printf("array ");
	while (array[s] != -1){
		printf("%d ", array[s]);
		s++;
	}
	printf("\n");
#endif
	if (N == 1){
		array[now] = p[now];
		return 0;
	}
	int leftnum = N / 2;
	int rightnum = N - N / 2;
#ifndef NDEBUG
	printf("N %d now %d\n", N, now);
#endif
	long long sum = merge(leftnum, now);
	for (int i = 0; i < rightnum; i++){
		int pi = p[now + leftnum + i];
		int fi = f[now + leftnum + i];
		int lowtarget = pi - fi;
		int uptarget = pi + fi;
		int upbound = now + leftnum - 1;
		int lowbound = now;
#ifndef NDEBUG
		printf("start %d end %d pi %d fi %d\n", now, now + leftnum - 1, pi, fi);
#endif
		if (array[upbound] < lowtarget || array[lowbound] > uptarget){
			continue;
		}
		int mid;
		while (upbound >= lowbound){
			mid = lowbound + (upbound - lowbound) / 2;
			if (array[mid] >= lowtarget){
				upbound = mid - 1;
			}
			else if (array[mid] < lowtarget){
				lowbound = mid + 1;
			}
		}
		if (array[mid] < lowtarget)
			mid = mid + 1;
		int leftindex = mid;
		upbound = now + leftnum - 1;
		lowbound = now;
		while (upbound >= lowbound){
			mid = lowbound + (upbound - lowbound) / 2;
			if (array[mid] > uptarget){
				upbound = mid - 1;
			}
			else if (array[mid] <= uptarget){
				lowbound = mid + 1;
			}
		}
		if (array[mid] > uptarget)
			mid = mid - 1;
		int rightindex = mid;
		sum += (rightindex - leftindex) + 1;
	}
	sum += merge(rightnum, now + leftnum);
	vector<int> leftarray(&array[now], &array[now] + leftnum);
	vector<int> rightarray(&array[now] + leftnum, &array[now] + N);
	int leftidx = 0, rightidx = 0;
	for (int i = now; i < now + N; i++){
		if (leftidx >= leftnum && rightidx >= rightnum)
			break;
		if (leftidx >= leftnum){
			array[i] = rightarray[rightidx];
			rightidx++;
			continue;
		}
		if (rightidx >= rightnum){
			array[i] = leftarray[leftidx];
			leftidx++;
			continue;
		}
		if (leftarray[leftidx] <= rightarray[rightidx]){
			array[i] = leftarray[leftidx];
			leftidx++;
		}
		else{
			array[i] = rightarray[rightidx];
			rightidx++;
		}
	}
	return sum;
}

int main(){
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++){
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < N; i++){
        scanf("%d", &f[i]);
    }
    for (int i = 0; i < MAXN; i++)
    	array[i] = -1;
    long long sum = merge(N, 0);
    printf("%lld\n", sum);
#ifndef NDEBUG
    int s = 0;
	printf("array ");
	while (array[s] != -1){
		printf("%d ", array[s]);
		s++;
	}
#endif		
}
