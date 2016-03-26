/***********************************************************************************
* 		Name: functions.c
*		Purpose: Contains all the helper functions for the project.
*		Author: Vignesh Kannan
*		Version: 0.1
*		Date:03/23/2016
************************************************************************************/
#include "header.h"
extern object_table *table;

//Might want to visit the function again to clean up the cell storage system
void free_object(object *id)
{
	free(id->variable_name);
	free(id);
	id = NULL; 
}

transaction_identifier* begin_transaction()
{
	transaction_identifier *node = NULL;
	node = (transaction_identifier *)malloc(sizeof(transaction_identifier));

	node->id = trans_id++;
	node->status = PENDING;
	return node;
}
//Using variable arguments for logging
// The possible strings are BEGIN_TRANSACTION, CHANGE, OUTCOME, END_TRANSACTION

void LOG(int log_option, ...)
{
	va_list argp;
	va_start(argp, log_option);
	switch (log_option)
	{
	case BEGIN_TRANSACTION:
			{
							  fp_log_file = fopen(LOG_FILE, "a");
							  fwrite("BEGIN_TRANSACTION\n", 1, strlen("BEGIN_TRANSACTION\n"), fp_log_file);
							  fclose(fp_log_file);
				  break;
			}
	case CHANGE:
			{
							  char *string; //Maximum 100 characters long
							  transaction_identifier* my_id;
							  fp_log_file = fopen(LOG_FILE, "a");
							  int a = ftell(fp_log_file);
							  my_id = va_arg(argp, transaction_identifier *);
							  fwrite("CHANGE ", 1, sizeof("CHANGE"), fp_log_file);
							  fprintf(fp_log_file, "%ld ", my_id->id);
							  fputc('\n', fp_log_file);
							  string = va_arg(argp, char*);
							  fwrite(string, 1, strlen(string), fp_log_file);  //Redo action
							  fputc('\n', fp_log_file);
							  fwrite(string, 1, strlen(string), fp_log_file);  //Undo action
							  fputc('\n', fp_log_file);
							  a = ftell(fp_log_file);
							  fclose(fp_log_file);
				break;
			}
	case OUTCOME:
			{
					int outcome;
					transaction_identifier* my_id;
					fp_log_file = fopen(LOG_FILE, "a");
					int a = ftell(fp_log_file);
					fwrite("OUTCOME ", 1, strlen("OUTCOME "), fp_log_file);
					outcome = va_arg(argp, int);
					if (outcome == 1)
						fwrite("COMMITTED ", 1, strlen("COMMITTED "), fp_log_file);
					else if (outcome == 2)
						fwrite("ABORTED ", 1, strlen("ABORTED "), fp_log_file);
					my_id = va_arg(argp, transaction_identifier*);
					fprintf(fp_log_file, "%ld ", my_id->id);
					a = ftell(fp_log_file);
					fputc('\n', fp_log_file);
					fclose(fp_log_file);
					break;
			}
	case END_TRANSACTION:
			{
							transaction_identifier* my_id;
							fp_log_file = fopen(LOG_FILE, "a");
							fwrite("END_TRANSACTION ", 1, strlen("END_TRANSACTION "), fp_log_file);
							my_id = va_arg(argp, transaction_identifier*);
							fprintf(fp_log_file, "%ld ", my_id->id);
							fputc('\n', fp_log_file);
							fclose(fp_log_file);
							free(my_id);
							break;
			}
	default:
			{
			   perror("Not a valid log code\n");
							  break;
			}
		va_end(argp);
	}
}
/*
Structure of the object table as below
It would have number of elements and linked list of all the objects. 
*/
int init_cell_storage()
{
	//Fseek to 1024*1024 file offset to make sure the Cell storage file is 1MB.
	fseek(fp_cell_storage_system, SIZE_OF_FILE_SYSTEM, SEEK_SET);
	//Write Random data for size. Technically increasing the size to 1025KB
	fputc('\n', fp_cell_storage_system);
	//Seek to the start of cell storage system
	object_table *table = (object_table*)malloc(sizeof(object_table));
	table = (object_table*)malloc(sizeof(table));
	table->offset = 512;
	table->elements = 0;
	table->list = NULL;
	write_table_to_file(table);
	fclose(fp_cell_storage_system);
	return 0;
}
