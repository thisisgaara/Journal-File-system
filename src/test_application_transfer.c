/***********************************************************************************
* 		Name: test_application_transfer.c
*		Purpose: Contains line by line copy of the same procedure as pg 9-623, Figure 9.19
*		Author: Vignesh Kannan
*		Version: 0.1
*		Date:03/24/2016
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
		LOG(OUTCOME, COMMITTED, my_id);
	else
	{
		LOG(OUTCOME, ABORTED, my_id);
		perror("Action not allowed. Would make debit account negative");
	}
	LOG(END_TRANSACTION, my_id);
	//Write after log
	PUT(debit_account, dbvalue.new_v);
	PUT(credit_account, crvalue.new_v);
	GET(debit_account, my_id);
	printf("\nThe output %d\n", debit_account->data);
}

int user_applications()
{
	int debit = 10447;
	int credit = 10787;
	//Create objects for the above variables
	object *debit_o, *credit_o;
	int i;
	//Sending integer to the object
	debit_o = allocate("debit", 10447);
	write(debit_o, 0);
	credit_o = allocate("credit", 10787);
	write(credit_o, 0);
	TRANSFER(debit_o, credit_o, 2000);
	return 0;
}
