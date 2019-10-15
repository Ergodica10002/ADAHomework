#include <stdio.h>
#include <string.h> 
#define NDEBUG
int dp[2500][2500] = {{0}};
int replace[2500][2500] = {{0}};
int min3(int a, int b, int c){
	if (a <= b && a <= c)
		return a;
	else if (b <= a && b <= c)
		return b;
	return c;
}
int main(void)
{
	char s1[2500];
	char s2[2500];
	scanf("%s%s", s1, s2);
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	for (int i = 0; i < l1; i++)
		dp[i][0] = i + (s1[i] == s2[0]);
	for (int i = 0; i < l2; i++)
		dp[0][i] = i + (s1[0] == s2[i]);
	dp[0][0] = (s1[0] == s2[0]);
	int min = 2147483647;
	for (int i = 1; i < l1; i++){
		for (int j = 1; j < l2; j++){
			dp[i][j] = min3(dp[i][j - 1] + 1, dp[i - 1][j] + 1, dp[i - 1][j - 1] + (s1[i] == s2[j]));
			if (dp[i][j] == (dp[i - 1][j - 1] + (s1[i] == s2[j])))
				replace[i][j] = 1;
		}
	}
	for (int i = 0; i < l2; i++){
		dp[l1][i] = dp[l1 - 1][i] + ((s1[l1 - 1] == s2[i]) && (replace[l1 - 1][i] == 0));
		if (dp[l1][i] < min){
			min = dp[l1][i];
		//	printf("%d %d %d\n", l1, i, min);
		}
	}
	for (int i = 0; i < l1; i++){
		dp[i][l2] = dp[i][l2 - 1] + ((s1[i] == s2[l2 - 1]) && (replace[i][l2 - 1] == 0));
		if (dp[i][l2] < min)
			min = dp[i][l2];
	}
#ifndef NDEBUG
	for (int i = 0; i <= l1; i++){
		for (int j = 0; j <= l2; j++)
			printf("%d ", dp[i][j]);
		printf("\n");
	}
#endif
	if (l1 == 1 || l2 == 1){
		if (s1[0] == s2[0])
			min = 1;
		else
			min = 0;
	}
	printf("%d\n", min);

	return 0;
}

