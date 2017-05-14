/**
 * CS 2110 - Summer 2012 - Homework #10
 * Edited by: Brandon Whitehead, Andrew Wilder
 *
 * Kenny Wu		7/24/13
 *
 * list.c: Complete the functions!
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION DO NOT PUT IT IN OTHER FILES */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
    /// @todo Implement changing the return value!
	node *createNode = malloc(sizeof(node));
	createNode->prev = NULL;
	createNode->next = NULL;
	createNode->data = data;
    
	return createNode;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
    /// @todo Implement changing the return value!
	list *createList = malloc(sizeof(list));
	createList->head = NULL;
	createList->tail = NULL;
	createList->size = 0;

    return createList;
}

/** push_front

  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{
    /// @todo Implement
	node *newFront = create_node(data);

	if(is_empty(llist))
	{
		//head and tail point to new node
		llist->head = newFront;
		llist->tail = newFront;
	}
	else
	{
		newFront->next = llist->head;
		llist->head->prev = newFront;
		llist->head = newFront;
	}

	llist->size++;
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
    /// @todo Implement
	node *newBack = create_node(data);

	if(is_empty(llist))
	{
		llist->head = newBack;
		llist->tail = newBack;
	}
	else
	{
		newBack->prev = llist->tail;
		llist->tail->next = newBack;
		llist->tail = newBack;
	}

	llist->size++;

}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
    /// @todo Implement
    /// @note remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.

	//save the location of the head
	node *frontNode = llist->head;
	//save location of the next 
	//node *nextNode = llist->head->next;
	int numEle1 = size(llist);

	//if the list is not empty	
	if(!(is_empty(llist)))
	{
		//if there is only 1 node in the list
		if(numEle1 == 1)
		{		
			free_func(frontNode->data);
			free(frontNode);
		}
		else
		{
			llist->head = frontNode->next;
			free_func(frontNode->data);
			free(frontNode);
			llist->head->prev = NULL;
		}

		llist->size--;

		return 0;
	}

    return -1;
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
    /// @todo Implement
    /// @note Remember to also free the node itself
    /// @note free_func is a function that is responsible for freeing the node's data only.

	int numEle2 = size(llist);
	node *prevNode = llist->tail;

	//if the list is not empty	
	if(!(is_empty(llist)))
	{
		//if there is only 1 node in the list
		if(numEle2 == 1)
		{				
			free_func(prevNode->data);
			free(prevNode);
		}
		else
		{
			llist->tail = prevNode->prev;
			free_func(prevNode->data);
			free(prevNode);
			llist->tail->next = NULL;
		}

		llist->size--;

		return 0;
	}

    return -1;
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param llist A pointer to the linked list to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *        data that's being used in this linked list, allocating space for
  *        every part of that data on the heap
  * @return The linked list created by copying the old one
  */
list* copy_list(list* llist, list_cpy copy_func)
{
	/// @todo implement
	list *nList = create_list();
	node* nNode = llist->head;

	for(int i = 0; i < size(llist); i++)
	{
		node *copy = copy_func(nNode->data);
		push_back(nList, copy);
		nNode = nNode->next;
	}
	nList->size = llist->size;

	return nList;
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
    /// @todo Implement changing the return value!
    /// @note you are returning the HEAD's DATA not the head node. Remember the user should never deal with the linked list nodes.
	if(llist->head != NULL)
	{
		return llist->head->data;
	}

    return NULL;
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
    /// @todo Implement changing the return value!
	if(llist->tail != NULL)
	{
		return llist->tail->data;
	}

    return NULL;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
    ///@note simply return the size of the linked list.  Its that easy!
	int lsize = llist->size;

    return lsize;
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
    /// @todo Implement
	node* nextNode = llist->head;

	for(int i = 0; i < size(llist); i++)
	{
		do_func(nextNode->data);
		nextNode = nextNode->next;	
	}
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
    /// @todo Implement changing the return value!
    /// @note remember to also free all nodes you remove.
    /// @note be sure to call pred_func on the NODES DATA to check if the node needs to be removed.
    /// @note free_func is a function that is responsible for freeing the node's data only.

	//save the next node
	node *cur = llist->head;

	static int removed = 0;
	int s = size(llist);

	for(int i = 0; i < s; i++)
	{
		//if the list is empty
		if(!(s))
		{
			return removed;
		}

		if(pred_func(cur->data))
		{
			//back of list
			if(cur->next == NULL)
			{
				remove_back(llist, free_func);
			}

			//front of list
			else if(cur->prev == NULL)
			{
				remove_front(llist, free_func);
			}

			//one node
			else if(cur->next == cur->prev)
			{
				remove_back(llist, free_func);
				removed++;
				return removed;
			}

			//other nodes
			else	
			{
				cur->next->prev = cur->prev;
            	cur->prev->next = cur->next;
				free_func(cur->data);
				free(cur);
				//llist->head = cur->next;
				llist->size--;
			}

			removed++;
		}
		cur = cur->next;
	}
    return removed;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    ///@note an empty list by the way we want you to implement it has a size of zero and head points to NULL.
	//if((llist->size == 0)&&(llist->head == NULL))
	if(!(llist->size))
	{
		return 1;
	}

    return 0;
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  *
  */
void empty_list(list* llist, list_op free_func)
{
    /// @todo Implement
    /// @note Free all of the nodes not the linked list itself.
    /// @note do not free llist.

	//traverse through the list and free up all data
	traverse(llist, free_func);
	node *hnode = llist->head;
	node *nnode = hnode->next;

	//free up all the nodes
	for(int i = 0; i < size(llist); i++)
	{
		free(hnode);		
		hnode = nnode;
    }

    llist->head = NULL;
    llist->tail = NULL;
    llist->size = 0;

}
