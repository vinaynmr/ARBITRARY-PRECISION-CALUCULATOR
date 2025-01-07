#include "main.h"
extern int sign1;
extern int sign2;
int substraction(dlist *temp1,dlist *temp2,dlist **head,dlist **tail)
{
	int res,ret;
	//traverss to each node and perform substraction
	while(temp1 != NULL)
	{
		//if list is not empty perform substractio
		if(temp2 != NULL)
		{
			//first list value is less than second list
			if((temp1 -> val) < (temp2 -> val))
			{
				//borrow from previous nodes
				ret = borrow_from_prev_nodes(temp1 -> prev);
				if(ret == SUCCESS)
					temp1 -> val += 10;
				else
					return FAILURE;
				//then o=perform substraction
				res = (temp1 -> val) - (temp2 -> val);
			}else
				//if first list is greater then 2nd list then directly perform substraction
				res = (temp1 -> val) - (temp2 -> val);
			//updating the result list
			ret = insert_at_first(head,tail,res);
			if(ret == FAILURE)
				return FAILURE;
		}else{
			//if one list is empty
			ret = insert_at_first(head,tail,temp1 -> val);
			if(ret == FAILURE)
				return FAILURE;
		}
		//traversing both list to their previous nodes
		temp1 = temp1 -> prev;
		if(temp2 != NULL)
			temp2 = temp2 -> prev;
	}
	return SUCCESS;
}



int borrow_from_prev_nodes(dlist *temp)
{
	//traversing untill they find the non zero natural  number
	while(temp != NULL)
	{
		//if traversed node has non zero data
		if(temp -> val > 0)
		{
			temp -> val -= 1;
			return SUCCESS;
		}
		temp -> val = 9;
		temp = temp -> prev;
	}
	return FAILURE;
}


int substraction_preprocess(char *argv[],dlist **head1,dlist **head2,dlist **tail1,dlist **tail2,dlist **temp1,dlist **temp2)
{
	int list_count1 = 0,list_count2 = 0;
	//insert strings in the list
	int ret = insert_strings(argv,head1,head2,tail1,tail2);
	if(ret == FAILURE)
	{
		printf("Creating List is failed!!\n");
		return 0;
	}
	//count number of nodes in list
	ret = count_nodes(*head1,*head2,&list_count1,&list_count2);
	if(ret == FAILURE)
		return FAILURE;
	*temp1 = NULL;*temp2 = NULL;
	//compare and assign list for the temprary pointers
	compare_and_assign(list_count1,list_count2,*head1,*head2,*tail1,*tail2,temp1,temp2);
	if(temp1 == NULL && temp2 == NULL)
		return FAILURE;
	return SUCCESS;
}

void compare_and_assign(int count1,int count2,dlist *head1,dlist *head2,dlist *tail1,dlist *tail2,dlist **temp1,dlist **temp2)
{
	//check which list has more node count and assign that list tail to temp1 pointer
	if(count1 > count2)
	{
		*temp1 = tail1;
		*temp2 = tail2;
	}else if(count2 > count1)
	{
		*temp1 = tail2;
		*temp2 = tail1;
	}else{
		//if both list node count is equal
		dlist *t1 = head1;
		dlist *t2 = head2;
		//treverse and find out which list is greater
		while(t1 != NULL)
		{
			if((t1 -> val) > (t2 -> val))
			{
				*temp1 = tail1;
				*temp2 = tail2;
				break;
			}else if((t1 -> val) < (t2 -> val))
			{
				*temp1 = tail2;
				*temp2 = tail1;
				break;
			}
			t1 = t1 -> next;
			t2 = t2 -> next;
		}
		//if both list are equal
		if(*temp1 == NULL)
		{
			*temp1 = tail1;
			*temp2 = tail2;
		}
	}
}
