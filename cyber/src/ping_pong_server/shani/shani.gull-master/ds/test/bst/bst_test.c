#include <stdio.h> /* gotta love 'em printfs */
#include "../../include/bst/bst.h"
extern int Intcompare(const void *data, const void *param)
{
	if (*(int *)data < *(int *)param)
	{
		return -1;
	}
	if (*(int *)data > *(int *)param)
	{
		return 1;
	}
	return 0;
}

extern int ActionPrint(void *data, void *param)
{
	printf("%d\n", *(int *)data);
	return 0;
}

static void TreeData(bst_t *bst)
{
	char *no = "no", *yes = "yes";
	printf("size of tree = %ld\n", BSTSize(bst));
	printf("is list empty? %s\n", (BSTIsEmpty(bst) ? yes : no));
	printf("height of tree = %ld\n", BSTHeight(bst));
	printf("Look at my tree, my tree is amazing\n give it a lick:\n\n");
	BSTPrint(bst, 5, 6);
}
int main(void)
{
	bst_t *bst = NULL;
	int arr[5] = {5, -2, 3, 14, 12};
	int to_insert[] = {10,20,30,40,50,60,70,80};
    int to_insert2[] = {21,5,25,1,9,19,40,0,4,7,12,18,22,29,50};
	int i = 0;
	/*bst = BSTCreate(&Intcompare);
	for (i = 0; i < 8; ++i)
	{
		BSTInsert(bst, &to_insert[i]);
	}
	TreeData(bst);
	BSTDestroy(bst);*/
	bst = BSTCreate(&Intcompare);
	for (i = 0; i < 5; ++i)
	{
		BSTInsert(bst, &arr[i]);
	}
	TreeData(bst);

	printf("in order:\n");
	BSTForEach(bst, IN_ORDER, ActionPrint, NULL);
	printf("pre order:\n");
	BSTForEach(bst, PRE_ORDER, ActionPrint, NULL);
	printf("post order:\n");
	BSTForEach(bst, POST_ORDER, ActionPrint, NULL);

	printf("remove\n");
	for (i = 0; i < 4; ++i)
	{
		printf("remone round %d\n", i);
		BSTRemove(bst, &arr[i]);
	}
	TreeData(bst);
	
	printf("  - Destroy -\n");
	BSTDestroy(bst);

	return 0;
}

