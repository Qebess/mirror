#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct tNode{
	int value;
	struct tNode *l,*r;
} tNode;
tNode * addnode(int x, tNode* tree){
	if (tree == NULL){
		tree = (tNode*)malloc(sizeof(tNode));
		tree->value = x;
		tree->l = NULL;
		tree->r = NULL;
	}else if(x < tree->value){
		tree->l = addnode(x,tree->l);
	}else{
		tree->r = addnode(x,tree->r);
	}
	return tree;
}
bool check(tNode *t1, tNode *t2){
	return (t1 && t2)? check(t1->l,t2->l) && check(t1->r,t2->r): (!t1 && !t2);
}
void freeTree(tNode *tree){
	if(tree != NULL){
		freeTree(tree->l);
		freeTree(tree->r);
		free(tree);
	}
}
int main(){
	int m,n;
	scanf("%d %d",&m,&n);
	tNode *list_tree[m];
	int nums[m][n];
	for(int i = 0; i<m; i++){
		list_tree[i] = NULL;
	}

	for(int i = 0; i<m;i++){
		for(int j = 0; j<n; j++){
			scanf("%d",&nums[i][j]);
		}
	}

	for(int i = 0; i<m; i++){
		for(int j = 0 ; j<n; j++){
				list_tree[i] = addnode(nums[i][j],list_tree[i]);
		}
	}
	for(int i = 0; i<m-1; i++){
		for(int j = i+1; j <m; j++){
			if(list_tree[i] != NULL && list_tree[j] != NULL && check(list_tree[i],list_tree[j])){
				freeTree(list_tree[j]);
				list_tree[j] = NULL;
			}
		}
	}
	int count = 0;
	for(int i = 0; i<m;i++){
		if(list_tree[i] !=NULL){
			count++;
		}
	}
	printf("%d\n", count);
	return 0;
}
