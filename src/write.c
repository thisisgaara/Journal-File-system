/***********************************************************************************
* 		Name: write.c
*		Purpose: Contains functions to write table and the entire list to cell storage file
*		Author: Vignesh Kannan
*		Version: 0.1
*		Date:03/25/2016
************************************************************************************/
#include "header.h"

void write_table_to_file(object_table *table) //Recursive write of table to file system
{
	fseek(fp_cell_storage_system, TABLE_OFFSET, SEEK_SET);
	fwrite(table, 1, sizeof(table_obj_id), fp_cell_storage_system);
}
/*
Open cell storage system
Read table from cell storage
Update the number of elements in table
Update the list of object id's in table
Write the table back to file
Using the node offset in the arguments, seek to the location
Make the write
Close the cell storage system
*/
/*Any object write to the cell storage should go through this function*/
/*Function automatically appends in object table as well as place the object at offset specified*/
void write(object* node, int overwrite_flag)
{
	//When write is being done, the number of elements would go up by 1
	object_table *table_l = (object_table *)malloc(sizeof(object_table)); //l stands for local
	//Get new object
	fp_cell_storage_system = fopen(NAME_OF_CELL_STORAGE_SYSTEM, "r+b"); //Do a open-close so that the changes reflect on the next write

	if (overwrite_flag == 0)
	{
		//Feed it in the log file, using that get the offset for data block
		fseek(fp_cell_storage_system, TABLE_OFFSET, SEEK_SET);

		//Though I have the entire table available in table global variable,
		//Reading it again so that the system does can recover from crash
		fread(table_l, 1, sizeof(object_table), fp_cell_storage_system);

		//Update the number of elements in write
		table_l->elements++;
		//Insert the new node into object table
		insert(&table_l, node);
		//Writeback the table
		write_table_to_file(table_l);
		fclose(fp_cell_storage_system);

		fp_cell_storage_system = fopen(NAME_OF_CELL_STORAGE_SYSTEM, "r+b");
	}

	//Just get to the offset location to write
	fseek(fp_cell_storage_system, node->offset_location, SEEK_SET);
	//Having a file offset with the object simplifies writing
	fwrite(node, 1, sizeof(object), fp_cell_storage_system);
	fclose(fp_cell_storage_system);
}

/*
	1. Read table
	2. Check if the ref_id is present, then update the variable and write to file
	3. Else create one and write
*/
/* ASSUMPTION: IF THE VALUE GIVEN IS NEW, CALLER SHOULD FILL IN THE object accordingly by calling allocate */
void PUT(object* ref_id, int value)
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
		fclose(fp_cell_storage_system);
		//Create one and write
		write(ref_id, 0);
		return;
	}
	//Data is already present
	ref_id->data = value;
	fclose(fp_cell_storage_system);
	//Write to FS
	/***/
	write(ref_id, 1);
	free(table);
}