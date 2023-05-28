#ifndef __BST_H_CR4__ 
#define __BST_H_CR4__ 

#include <stddef.h> /* Used for size_t type */

typedef struct bst bst_t;
typedef int(*compfunc_t)(const void *data, const void *param);
typedef int(*action_t)(void *data, void *param);
typedef enum {
	PRE_ORDER,
	IN_ORDER, 
	POST_ORDER
	}traverse;

/* 
 * Description : this function will create a BST, that holds a user's compare function.
 * Arguments : compfunc - void pointer to user's compare function, which is called with two arguments that point
       to the objects being compared. the comparison function must return an integer less than, or  greater
       than  zero  if  the  first  argument is considered to be respectively less than,
       or greater than the second.
 * Return : pointer to BST.
 * time complexity : O(1)
 * space complexity : O(1)
 */
bst_t *BSTCreate(compfunc_t compfunc);

/* 
 * Description : this function will destroy the BST.
 * Arguments : bst - pointer to BST.
 * Return : void.
 * time complexity : O(n)
 * space complexity : O(n)
 */
void BSTDestroy(bst_t *bst);

/* 
 * Description : this function will count the size of the BST.
 * Arguments : bst - pointer to BST.
 * Return : the size of the BST.
 * time complexity : O(n)
 * space complexity : O(n)
 */
size_t BSTSize(const bst_t *bst);

/* 
 * Description : this function will check if the BST is empty.
 * Arguments : bst - pointer to BST.
 * Return : 1 if empty, 0 if full.
 * time complexity : O(1)
 * space complexity : O(1)
 */
int BSTIsEmpty(const bst_t *bst);

/* 
 * Description : this function will find the deepest brach and return it's height
 * Arguments : bst - pointer to BST.
 * Return : the height of the tree.
 * time complexity : O(n)
 * space complexity : O(n)
 */
size_t BSTHeight(const bst_t *bst);

/* 
 * Description : this function will insert data from user into tree. 
 * Arguments : bst - pointer to BST, data - pointer to data provided by user.
 * Return : pointer to inserted datat or NULL if insertion failed.
 * special note : any changes to data in the returned pointer 
 * 					can cause undefined behavior.
 * special note : any attempt to insert duplicate values, 
 * 					will cause undefined behavior.
 * time complexity : O(n)
 * space complexity : O(n)
 */
void *BSTInsert(bst_t *bst, const void *data);

/* 
 * Description : this function will remove the data requested from the BST.
 * Arguments : bst - pointer to BST, data - pointer to data to remove from tree.
 * Return : void
 * special note : trying to remove non existing element will cause
 * 					undefined behavior.
 * time complexity : O(log n)
 * space complexity : O(n)
 */
void BSTRemove(bst_t *bst, void *data);

/* 
 * Description : this function will Check if the given data exists in the BST 
 * and returns it if it exsits or if it does not return NULL
 * Arguments : bst - pointer to BST, data - pointer to data to find provided by user
 * Return : pointer to data if found, NULL if not found. 
 * special note :  any changes to data in the returned pointer 
 * 					can cause undefined behavior.
 * time complexity : O(n)
 * space complexity : O(n)
 */
void *BSTFind(bst_t *bst, const void *data);

/*
 * Description - this function traverses over the BST with chosen order-style 
 * and applies Action func with param on each node.
 * the function traverses in-order, pre-order or post-order, if traverse is found,
 * respectively, to be less than, equal to, or greater than 0
 * Arguments - bst - pointer to BST, ActionFunc - pointer to action func, 
 *              param - pointer to action func parameter, 
 *              order_type - either POST_ORDER, IN_ORDER or PRE_ORDER.
 * Return - integer value coresponding to user action function.
 * Time Complexity - O(n).
 * Space Complexity - O(n).
 */

int BSTForEach(bst_t *bst, traverse order_type, action_t ActionFunc, void *param);

void BSTPrint(bst_t *bst, int space, int count); 
#endif /* __BST_H_CR4__ */