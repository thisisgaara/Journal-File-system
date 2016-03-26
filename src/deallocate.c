/***********************************************************************************
* 		Name: deallocate.c
*		Purpose: Contains functions to remove ID from the object table
*		Author: Vignesh Kannan
*		Version: 0.1
*		Date:03/25/2016
************************************************************************************/
/*
1. internal fragmentation of data blocks is allowed considering trade-off with complexity. 
2. TO deallocate data, just take the pointer object off the object table.
3. Eventhough data block persists, there is no way to access it.
*/
#include "header.h"
void deallocate(object *obj)
{
	object_table* table = (object_table*)malloc(sizeof(object_table));
	fp_cell_storage_system = fopen(NAME_OF_CELL_STORAGE_SYSTEM, "r+b");
	//Feed it in the log file, using that get the offset for data block
	fseek(fp_cell_storage_system, TABLE_OFFSET, SEEK_SET);

	table = read(); //Table contains the entire data
	table = delete_obj_id(&table, &obj);
	write_table_to_file(table);
	fclose(fp_cell_storage_system);
	return;
}