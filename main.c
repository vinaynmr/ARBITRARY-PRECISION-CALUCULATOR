/*
NAME : VINAY M R
DATE : 3/1/25
DESCRIPTION : Arbitrary Precision Caluculator
sample input : ./v.out 12 + 12
sample output: The result of operand 12 and 12 with '+' operator is : 24
*/

#include "main.h"
//global variables for referrencei of signs in operands
int sign1 = 0,sign2 = 0;
int neg1 = 0,neg2 = 0;

int main(int argc,char *argv[])
{
	//function call for validation
	status ret = validation(argc,argv);
	if(ret == FAILURE){
		printf("Please give proper arguments!\n");
		return 0;
	}
	//6 pointers which form 3 list for use of operations
	dlist *head1 = NULL;
	dlist *tail1 = NULL;
	dlist *head2 = NULL;
	dlist *tail2 = NULL;
	dlist *head3 = NULL;
	dlist *tail3 = NULL;
	//temprary pointers which stores tail address in each operation
	dlist *temp1 = NULL,*temp2 = NULL;
	//different flags for referrence over operation
	int flag = 0,sub_flag = 0,sub_sign_flag = 0,add_flag = 0;
	dlist *check = NULL;
	switch(*argv[2])
	{
		//addition case
		case '+':
			//check for negative signs over operands
			if((neg1 && neg2 == 0) || (neg2 && neg1 == 0))
			{
				sub_flag = 1;
				goto sub_label;
			}else{
add_label:
				//pre process for addition operation
				ret = addition_preprocess(argv,&head1,&head2,&tail1,&tail2,&temp1,&temp2);
				if(ret == FAILURE)
				{
					printf("Addition preprocess has been Failed!!\n");
					return 0;
				}
				//actual addition operation funstion call
				ret = addition(temp1,temp2,&head3,&tail3);
				if(ret == FAILURE)
					printf("Addition Failed!\n");
				//flag refferrence for subtraction result
				if(add_flag)
					goto sub_finish_label;
			}
add_finish_label:
			printf("The result of operand %s and %s with '+' operator is : ",argv[1],argv[3]);
			//flag referrence for negative sign
			if(sub_flag)
			{
				int non_zero_count = 0;
				//count non zeros for specific result
				ret = non_zero_count_function(head3,&non_zero_count);
				if(non_zero_count)
				{
					if(check == tail1)
						printf("-");
					else if(tail2 == check)
						printf("-");
				}
			}
			//special case for negative sign
			if(neg1 && neg2)
				printf("-");
			//function call for printing list
			ret = print_list(head3,tail3);
			if(ret == FAILURE)
				return FAILURE;
			break;




		case '-':
			//flags referrence for negative signs
			if((neg1  && neg2 == 0) || (neg2 && neg1 == 0))
			{
				if(neg2 == 0 && neg1)
					sub_sign_flag = 1;
				add_flag = 1;
				goto add_label;
			}else{
sub_label:
				//substraction preprocess
				ret = substraction_preprocess(argv,&head1,&head2,&tail1,&tail2,&temp1,&temp2);
				if(ret == FAILURE)
				{
					printf("Substraction Preprocess has been Failed!!\n");
					return 0;
				}
				//check for greatest operand
				check = temp1;
				//substraction function call
				ret = substraction(temp1,temp2,&head3,&tail3);
				if(ret == FAILURE)
					printf("Substracion operation has failed!!\n");
				if(sub_flag)
					goto add_finish_label;
			}
sub_finish_label:
			printf("The result of %s and %s for '-' operator is : ",argv[1],argv[3]);
			//check for sign
			if(check != NULL)
			{
				if(check == tail1 && sign1)
					printf("-");
				else if(tail2 == check && sign2 == 0 && sign1 == 0)
					printf("-");
			}else if(sub_sign_flag)
				printf("-");
			//printing list
			ret = print_list(head3,tail3);
			if(ret == FAILURE)
				return FAILURE;
			break;



		case 'x':
			//forming list using strings
			ret	= insert_strings(argv,&head1,&head2,&tail1,&tail2);
			if(ret == FAILURE)
			{
				printf("Creating list has failed!!\n");
				return 0;
			}
			//multiplication function call
			ret = multiplication(tail1,tail2,&head3,&tail3);
			if(ret == FAILURE)
				printf("Multiplication has been failed!\n");
			printf("The multiplication of operands %s and %s with operator 'x' is: ",argv[1],argv[3]);
			//check for sign
			if((neg1 && neg2 == 0) || (neg1 == 0 && neg2))
				printf("-");
			//print result list
			ret = print_list(head3,tail3);
			if(ret == FAILURE)
				printf("Printing of multplication result has failed\n");
			break;



		case '/':
			//division preprocess to perform division
			ret = division_preprocess(argv,&head1,&head2,&tail1,&tail2,&temp1,&temp2);
			if(ret == FAILURE)
			{
				printf("Division Preprocess has been Failed!!\n");
				return 0;
			}else if(ret == GREATER_DENOMINATOR)
			{
				printf("The result of the operands %s and %s is : 0\n",argv[1],argv[3]);
				return 0;
			}
			//functio call for division operation
			ret = division(&head1,&temp1,&head2,&temp2,&head3,&tail3);
			if(ret == FAILURE)
			{
				printf("Divison has been Failed!!\n");
				return 0;
			}
			printf("The result or division for operands %s and %s for operator is '/': ",argv[1],argv[3]);
			//check for negative sign
			if((neg1 && neg2) || (neg1 == 0 && neg2 == 0))
				;
			else
				printf("-");
			//print result list
			ret = print_list(head3,tail3);
			if(ret == FAILURE)
				printf("Printing of division result has been Failed!!\n");
			break;


		default :
			printf("Give proper operator to execute!!!\n");
	}
}

int validation(int argc,char *argv[])
{
	//printf("%d\n",argc);
	//to perform project operation argument count should be 4 exact
	if(argc != 4)
		return FAILURE;
	int i;
	if(argv[2][1] != '\0')
		return FAILURE;
	//check given strings have sign and numbers only
	if(argv[1][0] == '+' || argv[1][0] == '-')
	{
		i = 1;
		sign1 = 1;
	}else if(argv[1][0] >= '0' && argv[1][0] <= '9')
		i = 0;	
	else
		return FAILURE;
	while(argv[1][i] != '\0')
	{
		if(isalpha(argv[1][i]))
			return FAILURE;
		i++;
	}
	//check given strings have sign and numbers only
	if(argv[3][0] == '+' || argv[3][0] == '-')
	{
		i = 1;
		sign2 = 1;
	}else if(argv[3][0] >= '0' && argv[3][0] <= '9')
		i = 0;	
	else
		return FAILURE;
	while(argv[3][i] != '\0')
	{
		if(isalpha(argv[3][i]))
			return FAILURE;
		i++;
	}
	//check for negative signs
	if(sign1)
	{
		if(argv[1][0] == '-')
			neg1 = 1;
	}
	if(sign2)
	{
		if(argv[3][0] == '-')
			neg2 = 1;
	}
	return SUCCESS;
}
