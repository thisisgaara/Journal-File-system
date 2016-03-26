/***********************************************************************************
* 		Name: linked_list.c
*		Purpose: Just singly linked list implementation to add objects to object table
*		Author: Vignesh Kannan
*		Version: 0.1
*		Date:03/24/2016
************************************************************************************/
#include "header.h"

void insert_table_obj_list_to_table(object_table **table, table_obj_id **objid)
{
	table_obj_id* node = *objid;
	table_obj_id* temp = (*table)->list;
	if (temp == NULL)
	{
		(*table)->list = node;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = node;
	}
}
void insert(object_table **table, object *new_obj)
{
	table_obj_id* node = (table_obj_id*)malloc(sizeof(table_obj_id));
	node->id = new_obj->object_id;
	node->next = NULL;
	node->offset = new_obj->offset_location;
	table_obj_id* temp = (*table)->list;
	if (temp == NULL)
	{
		(*table)->list = node;
	}
	else
	{
		while (temp ->next!= NULL)
		{
			temp = temp->next;
		}
		temp ->next = node;
	}
}
int search(object_table*table, int id)
{
	table_obj_id *obj_id = table->list;
	while (obj_id != NULL)
	{
		if (obj_id->id == id)
			return obj_id->offset;
		obj_id = obj_id->next;
	}
	return -1;
}
object_table * delete_obj_id(object_table **table, object **obj_id)
{
	table_obj_id *iter = (*table)->list;
	if (iter->id == (*obj_id)->object_id) //Deletion at start
	{
		(*table)->list = iter->next; 
		(*table)->elements--;
		free(iter);
		return *table;
	}
	else
	{
		while (iter->next->id != (*obj_id)->object_id)
		{
			iter = iter->next;
		}
		table_obj_id *temp = iter->next;
		iter->next = iter->next->next;
		free(temp);
	}
	(*table)->elements--;
	return *table;
}