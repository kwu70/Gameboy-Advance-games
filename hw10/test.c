#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Kenny Wu

/* Here we are going to write some functions to support a linked list that stores Students (first name, last name)  */
/* Here is the data the user in this case us will be storing into our linked list */
/* YOU ARE REQUIRED TO COMPLETE THIS PART */
typedef struct Student
{
	const char* first_name;
	const char* last_name;
} Student;

/* Example functions given to you. Understand why these are written this way As you will be writing your own functions for part 2*/
Student* create_student(const char* first_name, const char* last_name)
{
	Student* s = malloc(sizeof(Student));
	s->first_name = first_name;
	s->last_name = last_name;
	return s;
}

void print_student(void* data)
{
	printf("%s %s\n", ((Student*)data)->first_name, ((Student*)data)->last_name);
}

void free_student(void* data)
{
	// free structure.
	free(data);
}

void *copy_data(const void* data)
{
	const char *first = ((Student*)data)->first_name;
	const char *last = ((Student*)data)->last_name;

	return create_student(first, last);
}

int pred_name_match(const void* data)
{
	const char *first = ((Student*)data)->first_name;
	const char *last = ((Student*)data)->last_name;

	if(first == last)
	{
		return 1;
	}

	return 0;
}

/* This main function does a little testing
   Like all good CS Majors you are required to test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void) 
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();
  
  	/* What does an empty list contain?  Lets use our handy traversal function */
  	printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_student);
	printf("\n");

 	/* Lets add a student and then print */
 	push_front(llist, create_student("Nick", "Emmel"));
	//push_front(llist, create_student("last", "fuck"));
 	printf("TEST CASE 2\nA List with one student should print that student:\n");
 	traverse(llist, print_student);
 	printf("\n");
 	
 	/* Lets remove that student and then print */
 	remove_front(llist, free_student);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_student);
 	printf("\n");

 	/* Lets add two elements and then print */
 	push_front(llist, create_student("Scott", "Emmel"));
 	push_front(llist, create_student("David", "Johnson"));
 	printf("TEST CASE 4\nA List with two students should print those two students:\n");
 	traverse(llist, print_student);
 	printf("\n"); 	

  	/* Lets kill the list */
  	empty_list(llist, free_student);
 	printf("TEST CASE 5\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_student);	
	printf("\n");

	/* testing remove_front after empty_list */
 	remove_front(llist, free_student);
 	printf("TEST CASE 6\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_student);
 	printf("\n");

	/* testing remove_back after empty_list */
 	remove_back(llist, free_student);
 	printf("TEST CASE 7\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_student);
 	printf("\n");

	/* add three element then print */
 	push_back(llist, create_student("John", "A"));
 	push_front(llist, create_student("Sky", "B"));
	push_front(llist, create_student("LOL", "101"));
	push_back(llist, create_student("Test", "AB"));
	push_front(llist, create_student("Random", "101"));
 	printf("TEST CASE 8\nA List with three students:\n");
 	traverse(llist, print_student);
 	printf("\n"); 

	/* testing remove_front after empty_list */
	//remove_back(llist, free_student);
 	remove_front(llist, free_student);
	//remove_front(llist, free_student);
 	printf("TEST CASE 9\nremove front:\n");
 	traverse(llist, print_student);
 	printf("\n");

	/* testing remove_back after empty_list */
 	remove_back(llist, free_student);
 	printf("TEST CASE 10\nremove back:\n");
 	traverse(llist, print_student);
 	printf("\n");

	remove_back(llist, free_student);
 	printf("TEST CASE 10\nremove back:\n");
 	traverse(llist, print_student);
 	printf("\n");
 	
	printf("TEST CASE 11\nfront of list:\n");
	print_student(front(llist));
 	printf("\n");

	printf("TEST CASE 12\nback of list:\n");
	print_student(back(llist));
 	printf("\n");

	printf("TEST CASE 13\nlist size:\n");
	printf("%d\n", size(llist));
 	printf("\n");

	printf("TEST CASE 14\nIs the list empty?\n");
	if(!is_empty(llist))
	{
		printf("The list have data\n");
	}
	else
	{
		printf("The list is empty\n");
	}
 	printf("\n");

	printf("TEST CASE 15\nprint out list:\n");
 	traverse(llist, print_student);
 	printf("\n");

	list *newCopy = copy_list(llist, copy_data);
	printf("TEST CASE 16\nlist copy:\n");
 	traverse(newCopy, print_student);
 	printf("\n");

	empty_list(llist, free_student);
	empty_list(newCopy, free_student);
	printf("TEST CASE 17\nempty list, should print nothing:\n");
	traverse(newCopy, print_student);
 	printf("\n");

	push_front(llist, create_student("ONE", "ONE"));
	push_front(llist, create_student("LOL", "101"));
	push_front(llist, create_student("Test", "1"));
	push_front(llist, create_student("ZERO", "ZERO"));
	push_front(llist, create_student("Six", "List"));
	push_front(llist, create_student("ONE", "ONE"));
	printf("TEST CASE 18\nTesting remove if node from top and bottom of list:\n");
	traverse(llist, print_student);
	printf("\n");

	remove_if(llist, pred_name_match, free_student);
	printf("After remove_if:\n");
	traverse(llist, print_student);
	printf("\n");
	printf("number of data removed: %d\n", remove_if(llist,pred_name_match, free_student));
	printf("\n");

	remove_back(llist, free_student);
	remove_back(llist, free_student);
	push_back(llist, create_student("ONE", "ONE"));
	push_back(llist, create_student("Test", "2"));
	printf("TEST CASE 19\nTest remove if from center of list:\n");
	traverse(llist, print_student);
	printf("\n");

	remove_if(llist, pred_name_match, free_student);
	printf("After remove_if:\n");
	traverse(llist, print_student);
	printf("\n");

	empty_list(llist, free_student);
	push_back(llist, create_student("Last", "ONE"));
	printf("TEST CASE 20\nTest remove if for 1 item in list:\n");
	traverse(llist, print_student);
	printf("\n");

	remove_if(llist, pred_name_match, free_student);
	printf("After remove_if:\n");
	traverse(llist, print_student);
	printf("\n");

	printf("TEST CASE 21\nTest remove if for no item in list:\n");
	traverse(llist, print_student);
	printf("\n");

	remove_if(llist, pred_name_match, free_student);
	printf("After remove_if:\n");
	traverse(llist, print_student);
	printf("\n");

	printf("TEST CASE 22\nTest remove for 1 non removable item:\n");
	traverse(llist, print_student);
	printf("\n");

	remove_if(llist, pred_name_match, free_student);
	printf("After remove_if:\n");
	traverse(llist, print_student);
	printf("\n");

	empty_list(llist, free_student);
	printf("TEST CASE 23\nTest empty entire list again:\n");
	traverse(llist, print_student);
	printf("\n");

	printf("TEST CASE 24\nis the list empty?\n");
	if(!is_empty(llist))
	{
		printf("The list have data\n");
	}
	else
	{
		printf("The list is empty\n");
	}
 	printf("\n");

 	/* YOU ARE REQUIRED TO MAKE MORE TEST CASES THAN THE ONES PROVIDED HERE */
 	/* You will get points off if you do not you should at least test each function here */
 	
 	/* Testing over clean up*/
 	free(llist);
 	
  	return 0;
}
