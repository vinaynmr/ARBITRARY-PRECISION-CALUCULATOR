#include "main.h"
int addition(dlist *temp1,dlist *temp2,dlist **head,dlist **tail)
{
	int carry = 0,res = 0,ret;
	//run the loop till list one becomes NULL because list will have greater integer
	while(temp1 != NULL)
	{
		//untill 2nd list becomes NULL
		if(temp2 != NULL)
			res = temp1 -> val + temp2 -> val + carry;
		else
			res = temp1 -> val + carry; //2nd list becoming NULL
		//printf("%d ",res);
		//result is greater than 9
		if(res > 9){
			//insert function for updating the result list
			ret = insert_at_first(head,tail,res % 10);
			if(ret == FAILURE)
				return FAILURE;
			carry = 1;
		}else{
		//result is less than 9
			//insert function for updating the result list
			ret = insert_at_first(head,tail,res);
			if(ret == FAILURE)
				return FAILURE;
			carry = 0;
		}
		//traversing to previous list
		temp1 = temp1 -> prev;
		if(temp2 != NULL)
			temp2 = temp2 -> prev;
	}
	//at end if we are getting the carry for last numbers addition
	if(carry == 1)
	{
		carry = 0;
		//update the result list
		ret = insert_at_first(head,tail,1);
		if(ret == FAILURE)
			return FAILURE;
	}
	return SUCCESS;
}
int addition_preprocess(char *argv[],dlist **head1,dlist **head2,dlist **tail1,dlist **tail2,dlist **temp1,dlist **temp2)
{
	int list_count1 = 0,list_count2 = 0;
	//create lists using the strings
	int ret = insert_strings(argv,head1,head2,tail1,tail2);
	if(ret == FAILURE)
	{
		printf("Creating List is failed!!\n");
		return 0;
	}
	//printf("%d\n",(*head2) -> val);
	//count the number of nodes in 2 lists
	ret = count_nodes(*head1,*head2,&list_count1,&list_count2);
	if(ret == FAILURE)
		return FAILURE;
	if(*head1 == NULL || *head2 == NULL)
		return FAILURE;
	*temp1 = NULL;*temp2 = NULL;
	//check for the greater integer list
	if(list_count1 > list_count2){
		*temp1 = *tail1;
		*temp2 = *tail2;
	}else {
		*temp1 = *tail2;
		*temp2 = *tail1;
	
	}
	return SUCCESS;
}
