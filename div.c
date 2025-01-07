#include "main.h"
extern int sign1;
extern int sign2;
int division_preprocess(char *argv[],dlist **head1,dlist **head2,dlist **tail1,dlist **tail2,dlist **temp1,dlist **temp2)
{
	//check the length of the string to know the size
	int len1 = strlen(argv[1]);
	int len2 = strlen(argv[3]);
	//check the numerator is less than denomiator to return zero
	if(len1 < len2)
		return GREATER_DENOMINATOR;
	else if(len1 == len2)
	{
		//even if list is equal there is a chance of deni=ominatore is zero
		int i1 = 0,i2 = 0;
		//check for the signs and tart checking
		if(sign1)
			i1 = 1;
		if(sign2)
			i2 = 1;
		if(i1 == 1 && i2 == 0)
			return GREATER_DENOMINATOR;
		//start checking each value by comparing each other
		while(argv[1][i1] != '\0')
		{
			if(argv[1][i1] < argv[3][i2])
				return GREATER_DENOMINATOR;
			else
				i1++;i2++;
		}
	}
	//then call insert at strings wich will form list using strings
	int ret = insert_strings(argv,head1,head2,tail1,tail2);
	if(ret == FAILURE)
		return FAILURE;
	*temp1 = *tail1,*temp2 = *tail2;
	return SUCCESS;
}


int division(dlist **head1,dlist **temp1,dlist **head2,dlist **temp2,dlist **head,dlist **tail)
{
	dlist *res_head = NULL,*res_tail = NULL;
	int ret,count1 = 0,count2 = 0;
	//loop should rn until the result becomes zero or less than zero
	while(1)
	{
		//each time substraction function call happens
		ret = substraction(*temp1,*temp2,head,tail);
		if(ret == FAILURE)
			return FAILURE;
		//counts the no of nodes in the result list
		ret = div_count(&res_head,&res_tail);
		if(ret == FAILURE)
			return FAILURE;
		//checks for greater denominator
		ret = check_for_greater_denominator(*head2,*temp2,*head,*tail);
		if(ret == GREATER_DENOMINATOR)
			break;
		else if(ret == FAILURE)
			return FAILURE;
		//print_list(*head,*tail);
		//printf("\n");
		//deleting the list
		ret = free_list(head1,temp1);
		if(ret == FAILURE || ret == LIST_EMPTY)
			return FAILURE;
		*temp1 = *tail;*head1 = *head;
		*head = *tail = NULL;
	}
		//print_list(*head,*tail);
	//deleting the list
	ret = free_list(head1,temp1);
	if(ret == FAILURE || ret == LIST_EMPTY)
		return FAILURE;
	//deleting the list
	ret = free_list(head,tail);
	if(ret == FAILURE || ret == LIST_EMPTY)
		return FAILURE;
	//storing head and tail address of result list for the referrence in main function
	*head = res_head;*tail = res_tail;
	return SUCCESS;
}

int div_count(dlist **head,dlist **tail)
{
	dlist *temp = *tail;
	//result list formation
	while(temp != NULL)
	{
		//condition to add for list
		if(temp -> val < 9)
		{
			temp -> val += 1;
			return SUCCESS;
		}
		temp -> val = 0;
		temp = temp -> prev;
	}
	//create a new node update data with 1 may be list first has become greater than 9 or first time
	int ret = insert_at_first(head,tail,1);
	if(ret == FAILURE)
		return FAILURE;
	else
		return SUCCESS;
}


int div_count_nodes(dlist *head1,dlist *head2,int *count1,int *count2)
{
	dlist *temp = head1;
	int flag = 0;
	//count the number of nodes in list1 excluding leading zero's
	while(temp != NULL)
	{
		//exclude leading zero's
		if(temp -> val != 0)
			flag = 1;
		if(flag)
			(*count1)++;
		temp = temp -> next;
	}
	temp = head2;
	flag = 0;
	//count the number of nodes in list1 excluding leading zero's
	while(temp != NULL)
	{
		//exclude leading zero's
		if(temp -> val != 0)
			flag = 1;
		if(flag)
			(*count2)++;
		temp = temp -> next;
	}
	return SUCCESS;
}

int check_for_greater_denominator(dlist *head2,dlist *tail2,dlist *head3,dlist *tail3)
{
	int count1 = 0,count2 = 0;
	//which will count the nodes in both operand lists
	int ret = div_count_nodes(head3,head2,&count1,&count2);
	if(ret == FAILURE)
		return FAILURE;
	//printf("count1 = %d and count2 = %d\n",count1,count2);
	//check which list is greater
	if(count1 < count2)
		return GREATER_DENOMINATOR;
	else if(count1 > count2)
		return SUCCESS;
	else{
		int flag = 0;
		dlist *temp1 = head3,*temp2 = head2;
		//if both list count are equal then by traversing check each number and confirm the greater list
		while(temp1 != NULL)
		{
			//printf("%d --- %d\n",temp1 -> val,temp2 -> val);
			if(temp1 -> val && temp2 -> val)
				flag = 1;
			if(flag)
			{	
				if((temp1 -> val) > (temp2 -> val))
					return SUCCESS;
				else if((temp1 -> val) < (temp2 -> val))
					return GREATER_DENOMINATOR;
				temp2 = temp2 -> next;
			}
			//traversing to find greater list
			temp1 = temp1 -> next;
		}
		return SUCCESS;
	}
}
