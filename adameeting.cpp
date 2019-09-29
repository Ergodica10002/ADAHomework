#include <stdio.h>
#include <stdlib.h>
#define MAXN 5000000
#define NDEBUG
int p[MAXN];
int f[MAXN];
typedef struct treenode{
	int p;
	struct treenode* left;
	struct treenode* right;
}treenode;
void printtree(treenode* root){
    if (root == NULL)
    	return;
    printtree(root->left);
    printf("%d ", root->p);
    printtree(root->right);
    return;
}
int findnum(treenode* root, int fi, int pi){
	if (root == NULL)
		return 0;
	if (pi - root->p > fi){
        return findnum(root->right, fi, pi);
	}
	if (root->p - pi > fi){
		return findnum(root->left, fi, pi);
	}
	return 1 + findnum(root->right, fi, pi) + findnum(root->left, fi, pi);	
}
void placenum(int pi, treenode* root){
	treenode* prev = root;
	while (root != NULL){
		prev = root;
		if (pi > root->p)
			root = root->right;
		else if (pi <= root->p)
			root = root->left;
	}
	root = (treenode*)malloc(sizeof(treenode));
	root->p = pi;
	root->left = root->right = NULL;
	if (pi > prev->p)
		prev->right = root;
	else
		prev->left = root;
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
	treenode* root = (treenode*)malloc(sizeof(treenode));
	root->p = p[0];
	root->left = root->right = NULL; 
    for (int i = 1; i < N; i++){
		sum = sum + findnum(root, f[i], p[i]);
        placenum(p[i], root);
#ifndef NDEBUG
        printtree(root);
        printf("\n");
#endif
    }
    printf("%d\n", sum);
}
