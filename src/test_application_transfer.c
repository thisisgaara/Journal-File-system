/***********************************************************************************
* 		Name: test_application_transfer.c
*		Purpose: Contains line by line copy of the same procedure as pg 9-623, Figure 9.19
*		Author: Vignesh Kannan
*		Version: 0.3
*		Date:04/02/2016
************************************************************************************/
//Functions from User applications would not be included in header
#include "header.h"
#include "user_header.h"
void TRANSFER(object* debit_account, object* credit_account, int amount)
{
	bank_account dbvalue;
	bank_account crvalue;
	transaction_identifier *my_id = begin_transaction();
	LOG(BEGIN_TRANSACTION);
	dbvalue.old_v = GET(debit_account, my_id);
	dbvalue.new_v = dbvalue.old_v - amount;
	crvalue.old_v = GET(credit_account, my_id);
	crvalue.new_v = crvalue.old_v + amount;
	LOG(CHANGE, my_id, "PUT(debit_account, dbvalue.new)", \
						"PUT(debit_account, dbvalue.old)");
	LOG(CHANGE, my_id, "PUT(credit_account, crvalue.new)", \
		"PUT(credit_account, crvalue.old)");
	if (dbvalue.new_v > 0)
	{
		LOG(OUTCOME, COMMITTED, my_id);
		//Write after log
		PUT(debit_account, dbvalue.new_v);
		PUT(credit_account, crvalue.new_v);
		LOG(END_TRANSACTION, my_id);
	}
	else
	{
		LOG(OUTCOME, ABORTED, my_id);
		printf("Action not allowed. Would make debit account negative");
		LOG(END_TRANSACTION, my_id);
	}
	printf("\nThe amount in debit account %d\n", debit_account->data);
	printf("\nThe amount in credit account %d\n", credit_account->data);
}

void create_clients()
{
	int i;
	int amount;
	char *str[10] = {
		"client 1",
		"client 2",
		"client 3",
		"client 4",
		"client 5",
		"client 6",
		"client 7",
		"client 8",
		"client 9",
		"client 10" };
	printf("\nCreating %d clients\n", NUMBER_OF_CLIENTS);
	object *clients[NUMBER_OF_CLIENTS];
	//Allocating client objects.
	for (i = 0; i < 5; i++)
	{
		printf("Enter the initial amount for client %d: ", i + 1);
		scanf("%d", &amount);
		clients[i] = allocate(str[i], amount);
		write(clients[i], 0);
		printf("\n");
	}
}

object* account_number_to_object(int i)
{
	return(GET_OBJECT(i));
}

void balance_enquiry()
{
	object_table* table = read();
	table_obj_id *obj;
	object *ret_obj = (object*)malloc(sizeof(object));
	FILE* fp_cell_storage_system = fopen(NAME_OF_CELL_STORAGE_SYSTEM, "r+b"); //Do a open-close so that the changes reflect on the next write
	obj = table->list;
	while (table->elements--)
	{
		fseek(fp_cell_storage_system, obj->offset, SEEK_SET);
		fread(ret_obj, 1, sizeof(object), fp_cell_storage_system);
		printf("%s => %d\n", ret_obj->variable_name, ret_obj->data);
		obj = obj->next;
	}
	fclose(fp_cell_storage_system);
	free(table);
}
void Transfer_abstraction()
{
	object* debit_o, *credit_o;
	int i, j, amount;
	printf("Enter the accounts you want the transfer to happen. Pattern: FromAccount1 ToAccount2 amount \n");
	scanf("%d %d %d", &i, &j, &amount);
	debit_o = account_number_to_object(i - 1);
	credit_o = account_number_to_object(j - 1);
	TRANSFER(debit_o, credit_o, amount);
	free(debit_o);
	free(credit_o);
}
void launch_thread()
{
	pthread_t thread;
	int rc = pthread_create(&thread, NULL, Transfer_abstraction, NULL);
	
	/* 
	int i, j, amount;
	printf("Enter the accounts you want the transfer to happen. Pattern: FromAccount1 ToAccount2 amount \n");
	scanf("%d %d %d", &i, &j, &amount);
	debit_o = account_number_to_object(i - 1);
	credit_o = account_number_to_object(j - 1);
	TRANSFER(debit_o, credit_o, amount);
	free(debit_o);
	free(credit_o);
	*/
}
int user_applications()
{
	create_clients();
	int i, j, amount;
	//Sending integer to the object
	while (1)
	{
		printf("Choose the option you want 1. Transaction 2. Balance enquiry 3. Exit\n");
		scanf("%d", &amount);//Reuse amount variable
		switch (amount)
		{
			case 1:
				{

					break;
				}
			case 2:
				{
					  balance_enquiry();
					  break;
				}
			case 3:
				{
					printf("Thank you\n");
					exit(0);
				}
			default:
				{
					printf("Invalid option\n");
					break;
				}
		}		
	}
	return 0;
	
}
