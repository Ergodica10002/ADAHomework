#include <stdio.h>
#define MAXN 50000000 
int p[MAXN];
int f[MAXN];
int array[MAXN];
void initarray(int *p){
    for (int i = 0; i < MAXN; i++)
        p[i] = -1;
    return;
}
int findnum(int now, int fi, int pi){
	if (array[now] == -1)
		return 0;
	if (pi - array[now] > fi){
        return findnum(now * 2, fi, pi);
	}
	if (array[now] - pi > fi){
		return findnum(now * 2 + 1, fi, pi);
	}
	return 1 + findnum(now * 2, fi, pi) + findnum(now * 2 + 1, fi, pi);		
}
void placenum(int pi){
	int now = 1;
	while (array[now] != -1){
//		printf("arraynow %d\n", array[now]);
		if (pi > array[now])
			now = now * 2;
		else if (pi <= array[now])
			now = now * 2 + 1;
	}
	array[now] = pi;
	return;
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
    int sum = 0;
	initarray(array);
	array[1] = p[0];
    for (int i = 1; i < N; i++){
		sum = sum + findnum(1, f[i], p[i]);
        placenum(p[i]);
        
    }
    printf("%d\n", sum);
}
