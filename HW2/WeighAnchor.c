#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAXN 210000
#define NDEBUG
//Reference: b07902062
int compare(const void *a, const void *b)
{
	int c = *(int *)a;
	int d = *(int *)b;
	if (c < d) 
		return -1;     
	else if (c == d) 
		return 0; 
	else 
		return 1;
}
void arrange(int* s1, int* s2, int* s3){
	int tmp;
	if (*s2 <= *s1 && *s2 <= *s3){
		tmp = *s1;
		*s1 = *s2;
		*s2 = tmp;
	}
	if (*s3 <= *s1 && *s3 <= *s2){
		tmp = *s1;
		*s1 = *s3;
		*s3 = tmp;
	}
	if (*s3 <= *s2){
		tmp = *s2;
		*s2 = *s3;
		*s3 = tmp;
	}
	return;
}
void findcount(int N, int count[7], int s1, int s2, int s3, int enemy[]){
	int s[7];
	s[0] = s1;
	s[1] = s2;
	s[2] = (s1 + s2 > s3)? s3 : (s1 + s2);
	s[3] = (s1 + s2 > s3)? (s1 + s2) : s3;
	s[4] = s1 + s3;
	s[5] = s2 + s3;
	s[6] = s1 + s2 + s3;
	int nowsi = 0;
	for (int i = 0; i < N; i++){
		while (s[nowsi] < enemy[i])
			nowsi++;
		count[nowsi]++;
	}

	return;
}

int counttime(int N, int enemy[], int s1, int s2, int s3){
	int c = 0;
	int count[7] = {0};
	int flag = (s1 + s2 > s3);
	findcount(N, count, s1, s2, s3, enemy);

#ifndef NDEBUG
	printf("%d %d %d %d %d %d %d\n", count[0], count[1], count[2], count[3], count[4], count[5], count[6]);
#endif
//case 123
	while (count[6] > 0){
		count[6]--;
		c++;
	}
//case23
	while (count[5] > 0){
		count[5]--;
		c++;
		if (count[0] > 0)
			count[0]--;
	}
//case13
	while (count[4] > 0){
		count[4]--;
		c++;
		if (count[1] > 0)
			count[1]--;
		else if (count[0] > 0)
			count[0]--;
	}
//case12 and case3
	if (flag){
		while (count[3] > 0){	//12
			count[3]--;
			c++;
			if (count[2] > 0)
				count[2]--;
			else if (count[1] > 0)
				count[1]--;
			else if (count[0] > 0)
				count[0]--;
		}
	}
	else {
		while (count[3] > 0){	//3
			count[3]--;
			c++;
			int g1 = 0, g2 = 0;
			if (count[0] > 0){
				count[0]--;
				g1 = 1;
			}
			if (count[1] > 0){
				count[1]--;
				g2 = 1;
			} else if (count[0] > 0){
				count[0]--;
				g2 = 1;
			}
			if (g1 == 0 && g2 == 0 && count[2] > 0){
				count[2]--;
			}
		}
	}
	while (count[2] > 0){
		count[2]--;
		c++;
		int g1 = 0, g2 = 0;
		if (count[0] > 0){
			count[0]--;
			g1 = 1;
		}
		if (count[1] > 0){
			count[1]--;
			g2 = 1;
		} else if (count[0] > 0){
			count[0]--;
			g2 = 1;
		}
		if (g1 == 0 && g2 == 0 && count[2] > 0){
			count[2]--;
		}
	}
//case 2
	while (count[1] > 0){
		count[1]--;
		c++;
		if (count[0] > 0)
			count[0]--;
		if (count[1] > 0)
			count[1]--;
		else if (count[0] > 0)
			count[0]--;
	}
//case1
	while (count[0] > 0){
		count[0] -= 3;
		c++;
	}
	
	return c;

}

int main(){
	int N;
	scanf("%d", &N);
	int s1, s2, s3;
	scanf("%d%d%d", &s1, &s2, &s3);
	int enemy[MAXN];
	for (int i = 0; i < N; i++)
		scanf("%d", &enemy[i]);
	arrange(&s1, &s2, &s3);
	qsort(enemy, N, sizeof(enemy[0]), compare);
	if (enemy[N - 1] > s1 + s2 + s3)
		printf("-1\n");
	else
		printf("%d\n", counttime(N, enemy, s1, s2, s3));

	return 0;
}
