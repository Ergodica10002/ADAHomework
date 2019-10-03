#include <stdio.h>
#include <string.h> 
int main(void)
{
	char s1[2500];
	char s2[2500];
	scanf("%s%s", s1, s2);
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	printf("%d\n", (l1 < l2)? l1 : l2);

	return 0;
}

