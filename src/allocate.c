/***********************************************************************************
* 		Name: allocate.c
*		Purpose: Contains functions to allocate resource on the cell storage and return a file offset to which 
				 write can happen to the caller
*		Author: Vignesh Kannan
*		Version: 0.1
*		Date:03/25/2016
************************************************************************************/
#include "header.h"
//Create a new object for user variable
//One of the important functions
//Allocate a location in cell storage, populate the structure and return 
object * create_new_object(char* name, int value)
{
	object* my_obj = NULL;
	my_obj = (object*)malloc(sizeof(object));
	my_obj->object_id = trans_id++;
	my_obj->variable_name = (char*)malloc(32); //Maximum 32 bytes for variable name
	strcpy(my_obj->variable_name, name);
	my_obj->data = value;
	my_obj->current_size = sizeof(int);
	my_obj->number_of_blocks = 1; //Wouldn't be of use unless large data
	//Initially thought of having a linked list implementation. But reading with file offset should suffice.
	my_obj->prev = NULL;
	my_obj->next = NULL;
	return my_obj;
}
/*
	1. Create new object
	2. Initialize the elements in struct
	3. Read the table from the cell storage so that the offset to which object can be written is calculated.
	4. Calculate the offset to write
*/
object* allocate(char* name, int value)
{
	object* new_obj = create_new_object(name, value);
	object_table *table_l = NULL;
	//Get new object
	fp_cell_storage_system = fopen(NAME_OF_CELL_STORAGE_SYSTEM, "r+b"); //Do a open-close so that the changes reflect on the next write
	table_l = read();
	fclose(fp_cell_storage_system);

	int offset = DATA_OFFSET + (table_l->elements * sizeof(object));
	new_obj->offset_location = offset;
	free(table_l);
	return new_obj;
}