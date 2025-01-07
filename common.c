extern int sign1;
extern int sign2;
int insert_strings(char *argv[],dlist **head1,dlist **head2,dlist ** tail1,dlist **tail2)
{
	int i = 0;
	status ret;
	dlist *temp = NULL,*temp1 = NULL;
	//check sign is present or not to form list
	if(sign1 == 1)
		i = 1;
	int flag = 0;
	//for every character create a node and form a list
	while(argv[1][i] != '\0')
	{
		if(argv[1][i] != '0')
			flag = 1;
		if(flag)
		{
			//printf("%c\n",argv[1][i]);
			ret = insert_at_last(head1,tail1,argv[1][i] - 48);
			if(ret == FAILURE)
				return FAILURE;
		}
		i++;
	}
	//check list is not formed 
	if(flag == 0)
	{
		ret = insert_at_last(head1,tail1,0);
		if(ret == FAILURE)
			return FAILURE;
	}
	i = 0;
	//check for the sign
	if(sign2 == 1)
		i = 1;
	flag = 0;
	//for every character create a node and form a list
	while(argv[3][i] != '\0')
	{
		if(argv[3][i] != '0')
			flag = 1;
		if(flag)
		{
			ret = insert_at_last(head2,tail2,argv[3][i] - 48);
			if(ret == FAILURE)
				return FAILURE;
		}
		i++;
	}
	//check if list formed or not
	if(flag == 0)
	{
		ret = insert_at_last(head2,tail2,0);
		if(ret == FAILURE)
			return FAILURE;
	}
	/*
	ret = print_list(*head1,*tail1);
	if(ret == FAILURE)
		return FAILURE;
	ret = print_list(*head2,*tail2);
	if(ret == FAILURE)
		return FAILURE;*/
	return SUCCESS;
}

int free_list(dlist **head,dlist **tail)
{
	//check list is already empty or not
	if(*head == NULL)
		return LIST_EMPTY;
	dlist *temp = *head;
	//by traversing free each nodes in list
	while(temp != NULL)
	{
		dlist *temp_before = temp;
		temp = temp -> next;
		free(temp_before);
	}
	*head = *tail = NULL;
	return SUCCESS;
}

int insert_at_first(dlist **head,dlist **tail,int data)
{
	//allocate memory to create a node
	dlist *new = malloc(sizeof(dlist));
	if(new == NULL)
		return FAILURE;
	//update new node
	new -> val = data;
	new -> prev = new -> next = NULL;
	//if list is empty
	if(*head == NULL)
	{
		*head = new;
		*tail = new;
		return SUCCESS;
	}
	//if list is not empty
	new -> next = *head;
	(*head) -> prev = new;
	*head = new;
	return SUCCESS;
}

int insert_at_last(dlist **head,dlist **tail,int data)
{
	//allocate memory to create a node
	dlist *new = malloc(sizeof(dlist));
	if(new == NULL)
		return FAILURE;
	//update new node
	new -> val = data;
	new -> prev = new -> next = NULL;
	//if list is empty
	if(*head == NULL)
	{
		*head = new;
		*tail = new;
		return SUCCESS;
	}
	//if list is not empty
	new -> prev = *tail;
	(*tail) -> next = new;
	*tail = new;
	return SUCCESS;
}

int print_list(dlist *head,dlist *tail)
{
	dlist *temp = head;
	int flag = 0,count = 0;
	//traverse to each node and print data i that node
	while(temp != NULL)
	{
		//should leading zero's
		if(temp -> val != 0)
			flag = 1;
		if(flag)
		{
			count++;
			printf("%d",temp -> val);
		}
		temp = temp -> next;
	}
	//list is not created
	if(count == 0)
		printf("0");
	printf("\n");
	return SUCCESS;
}

int count_nodes(dlist *head1,dlist *head2,int *count1,int *count2)
{
	//temprary pointer
	dlist *temp = head1;
	//by traversing count nodes in list
	while(temp != NULL)
	{
		(*count1)++;
		temp = temp -> next;
	}
	temp = head2;
	//by traversing count nodes in list
	while(temp != NULL)
	{
		(*count2)++;
		temp = temp -> next;
	}
	return SUCCESS;
}

int non_zero_count_function(dlist *head,int *non_zero_count)
{
	//travesing check non zeros in list
	while(head != NULL)
	{
		if(head -> val != 0)
			(*non_zero_count)++;
		head = head -> next;
	}
}

