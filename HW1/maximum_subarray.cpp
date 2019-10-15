#include <stdio.h>
#include <stdlib.h>
#define MAXN 600000
long long a[MAXN];
long long p[MAXN];
long long v[MAXN];
long long maxsum[MAXN] = {0};
long long max3(long long a, long long b, long long c){
	if (a >= b && a >= c)
		return a;
	else if (b >= a && b >= c)
		return b;
	return c;
}
long long max2(long long a, long long b){
	return (a > b)? a : b;
}
typedef struct treenode{
	int l,r;
	long long submax;
	long long sum;
	long long leftmax;
	long long rightmax;
	struct treenode* left;
	struct treenode* right;
}treenode;
treenode* buildtree(int left, int right){
	treenode* root = (treenode*)malloc(sizeof(treenode));
	root->l = left;
	root->r = right;
	if (left == right){
		root->sum = root->submax = root->leftmax = root->rightmax = a[left];
		root->left = root->right = NULL; 
		return root;
	}
	root->left = buildtree(left, (left + right) / 2);
	root->right = buildtree(((left + right) / 2) + 1, right);
	root->sum = root->left->sum + root->right->sum;
	//compute max left sum
	root->leftmax = max2(root->left->leftmax, root->left->sum + root->right->leftmax);
	//compute max right sum
	root->rightmax = max2(root->right->rightmax, root->right->sum + root->left->rightmax);
	root->submax = 
		max3(root->left->rightmax + root->right->leftmax, root->left->submax, root->right->submax);
	return root;
}
treenode* update(treenode* root, int pi, int vi, int beforev){
	if (root->l == root->r){
		root->sum += (vi - beforev);
		root->submax += (vi - beforev);
		root->leftmax += (vi - beforev);
		root->rightmax += (vi - beforev);
		return root;
	}
	int mid = (root->l + root->r) / 2;
	
	if (pi - 1 <= mid){
		root->sum += (vi - beforev);
		root->left = update(root->left, pi, vi, beforev);
		root->leftmax = max2(root->left->leftmax, root->left->sum + root->right->leftmax);
		root->rightmax = max2(root->right->rightmax, root->right->sum + root->left->rightmax);
		root->submax = 
			max3(root->left->rightmax + root->right->leftmax, root->left->submax, root->right->submax);
	}
	else{
		root->sum += (vi - beforev);
		root->right = update(root->right, pi, vi, beforev);
		root->leftmax = max2(root->left->leftmax, root->left->sum + root->right->leftmax);
		root->rightmax = max2(root->right->rightmax, root->right->sum + root->left->rightmax);
		root->submax = 
			max3(root->left->rightmax + root->right->leftmax, root->left->submax, root->right->submax);
	}
	return root;
}
int main(void)
{
	int N, Q;
	scanf("%d%d", &N, &Q);
	for (int i = 0; i < N; i++)
		scanf("%lld", &a[i]);
	for (int i = 0; i < Q; i++)
		scanf("%lld %lld", &p[i], &v[i]);
	treenode* root = buildtree(0, N - 1);
	printf("%lld\n", (root->submax > 0)? root->submax : 0);
	for (int i = 0; i < Q; i++){
		int beforev = a[p[i] - 1];
		a[p[i] - 1] = v[i];
		root = update(root, p[i], v[i], beforev);
		printf("%lld\n", (root->submax > 0)? root->submax : 0);
	}

	return 0;
}
