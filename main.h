#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<ctype.h>

//enums for returntypes to confirm the resul
typedef enum{
	FAILURE,
	SUCCESS,
	LIST_EMPTY,
	POSITION_NOT_FOUND,
	GREATER_DENOMINATOR
}status;

//node structure
typedef struct node{
	struct node *prev;
	int val;
	struct node *next;
}dlist;


//function declarations
int validation(int,char *argv[]);

int insert_strings(char **,dlist **head1,dlist **head2,dlist **tail1,dlist **tail2);
int count_nodes(dlist *head1,dlist *head2,int *count,int *count1);
int addition_preprocess(char *argv[],dlist **,dlist **,dlist **,dlist **,dlist **,dlist **);
int addition(dlist *,dlist *,dlist **,dlist **);
int non_zero_count_function(dlist *head,int *non_zero_count);


int substraction(dlist *,dlist *,dlist **,dlist **);
int substraction_preprocess(char *argv[],dlist **,dlist **,dlist **,dlist **,dlist **,dlist **);
void compare_and_assign(int count1,int count2,dlist *head1,dlist *head2,dlist *tail1,dlist *tail2,dlist **temp1,dlist **temp2);
int borrow_from_prev_nodes(dlist *temp);

int multiplication(dlist *,dlist *,dlist **,dlist **);
int append_zeros(dlist **head,dlist **tail,int count);
int free_list(dlist **head,dlist **tail);
int shift_list(dlist **head3,dlist **tail3,dlist **head1,dlist **tail1);

int division_preprocess(char *argv[],dlist **,dlist **,dlist **,dlist **,dlist **,dlist **);
int division(dlist **,dlist **,dlist **,dlist **,dlist **,dlist **);
int div_count(dlist **,dlist **);
int check_for_greater_denominator(dlist *,dlist *,dlist *,dlist *);
int div_count_nodes(dlist *,dlist *,int *,int *);

int insert_at_first(dlist **head,dlist **tail,int data);
int insert_at_last(dlist **head,dlist **tail,int data);
int print_list(dlist *head,dlist *tail);

#endif
