/***********************************************************************************
* 		Name: read.c
*		Purpose: Contains functions to read table and the necessary object from transaction ID
*		Author: Vignesh Kannan
*		Version: 0.1
*		Date:03/25/2016
************************************************************************************/
#include "header.h"
object_table * read()
{
	object_table* table = (object_table*)malloc(sizeof(object_table));
	fseek(fp_cell_storage_system, TABLE_OFFSET, SEEK_SET);
	//Though I have the entire table available in table global variable,
	//Reading it again so that the system does can recover from crash
	fread(table, 1, sizeof(object_table), fp_cell_storage_system);
	return table;
}
void print_iter(object_table* table) //Test function
{
	table_obj_id *id = table->list;
	while (id != NULL)
	{
		printf("%d %ld\t",id->id, id->offset);
		id = id->next;
	}
}

/* Redundancy added just in case
	1. Read object table
	2. Get the offset correspnding to the objid given
	3. Goto offset
	4. Read object and return
*/
int GET(object* ref_id, transaction_identifier* my_id)
{
	object_table *table = (object_table*)malloc(sizeof(object_table));
	fp_cell_storage_system = fopen(NAME_OF_CELL_STORAGE_SYSTEM, "r+b"); //Do a open-close so that the changes reflect on the next write

	//Feed it in the log file, using that get the offset for data block
	fseek(fp_cell_storage_system, TABLE_OFFSET, SEEK_SET);

	table = read(); //Table contains the entire data
	//print_iter(table);  //For testing purpose
	int offset = search(table, ref_id->object_id);
	if (offset == -1)
	{	
		perror("Data not found\n");
		exit(0);
	}
	fseek(fp_cell_storage_system, offset, SEEK_SET);
	object *ret_obj = (object*)malloc(sizeof(object));
	fread(ret_obj, 1, sizeof(object), fp_cell_storage_system);
	free(table);
	return ret_obj ->data;
}
