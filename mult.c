#include "main.h"
int multiplication(dlist *temp1,dlist *temp2,dlist **head,dlist **tail)
{
	dlist *h1 = NULL,*h2 = NULL,*t1 = NULL,*t2 = NULL,*h3 = NULL,*t3 = NULL;
	dlist *temp = NULL;
	int i = 0,res,carry = 0,count = 0,ret;
	//traversing and perform multiplication for each node
	while(temp1 != NULL)
	{
		temp = temp2;
		//nested loop for another list should repeat the first node times
		while(temp != NULL)
		{
			//multiplying the list and adding the zeros
			res = (temp -> val * temp1 -> val) + carry;
			carry = 0;
			//if result is greater thean 9 take carry and update the list with last digit
			if(res > 9)
			{
				//first outer loop iteration
				if(count == 0)
				{
					ret = insert_at_first(&h1,&t1,res % 10);
					if(ret == FAILURE)
						return FAILURE;
				}else{
					//non first outer loop iteration
					ret = insert_at_first(&h2,&t2,res % 10);
					if(ret == FAILURE)
						return FAILURE;
				}
				carry = res / 10;
			}else{
				//if result is not greater than zero directly update result list
				//1st outer loop iteration
				if(count == 0)
				{
					ret = insert_at_first(&h1,&t1,res);
					if(ret == FAILURE)
						return FAILURE;
				}else{
					//non 1st outer loop iteration
					ret = insert_at_first(&h2,&t2,res);
					if(ret == FAILURE)
						return FAILURE;
				}
			}
			temp = temp -> prev;
		}
		//if carry is remaaining after one iteration
		if(carry > 0)
		{
			if(count == 0)
			{
				ret = insert_at_first(&h1,&t1,carry);
				if(ret == FAILURE)
					return FAILURE;
			}else{
				ret = insert_at_first(&h2,&t2,carry);
				if(ret == FAILURE)
					return FAILURE;
			}
			carry = 0;
		}
		//add results of 2 list if it is greater than first iteration
		count++;
		if(count >= 2)
		{
			//addition function call
			ret = addition(t2,t1,&h3,&t3);
			if(ret == FAILURE)
				return FAILURE;
			//deleting list 1
			ret = free_list(&h1,&t1);
			if(ret == FAILURE)
				return FAILURE;
			//deleting list 2
			ret = free_list(&h2,&t2);
			if(ret == FAILURE)
				return FAILURE;
			//shifting the list3 to list1
			ret = shift_list(&h3,&t3,&h1,&t1);
			if(ret == FAILURE)
				return FAILURE;
			//deleting list3
			ret = free_list(&h3,&t3);
			if(ret == FAILURE)
				return FAILURE;
		}
		//append zero's iteration times after first iteration at start of list
		if(count > 0)
		{
			//function call for appending zero's
			ret = append_zeros(&h2,&t2,count);
			if(ret == FAILURE)
				return FAILURE;
		}
		temp1 = temp1 -> prev;
	}
	//storing list head and tail address in 2 pointers to reflect in main function
	*head = h1;
	*tail = t1;
	return SUCCESS;
}


int shift_list(dlist **head3,dlist **tail3,dlist **head1,dlist **tail1)
{
	if(*head1 != NULL)
		return FAILURE;
	if(*head3 == NULL)
		return LIST_EMPTY;
	dlist *temp = *head3;
	//shifting list to another list
	while(temp != NULL)
	{
		//insert at last funtion call
		int ret = insert_at_last(head1,tail1,temp -> val);
		if(ret == FAILURE)
			return FAILURE;
		temp = temp -> next;
	}
	return SUCCESS;
}

int append_zeros(dlist **head,dlist **tail,int count)
{
	//check list is empty
	if(*head != NULL)
		return FAILURE;
	//append zero count times 
	while(count > 0)
	{
		int ret = insert_at_last(head,tail,0);
		if(ret == FAILURE)
			return FAILURE;
		count--;
	}
	return SUCCESS;
}
