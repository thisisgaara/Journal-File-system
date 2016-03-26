/***********************************************************************************
* 		Name: header.h
*		Purpose: Contains fundamental data structures to be used by the program
*		Author: Vignesh Kannan
*		Version: 0.1
*		Date:03/24/2016
************************************************************************************/

#ifndef DECLARATION	
#define DECLARATION
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#define NAME_OF_CELL_STORAGE_SYSTEM "../jfs/JFS_Cell_storage_system"
#define SIZE_OF_FILE_SYSTEM 1024*1024 //1MB
#define LOG_FILE "../log/log_file.log"
#define TABLE_OFFSET 512 //Keeping it global so that it can be read easily by all
#define DATA_OFFSET 10240 //Keeping it global  10KB

//For logging
#define	BEGIN_TRANSACTION 0
#define	CHANGE			  1
#define	OUTCOME			  2 
#define	END_TRANSACTION   3

//Global variables
extern long int trans_id;

//Data structures
typedef struct
{
	int object_id;
	char *variable_name;
	int data;   //Can be changed later
 	int offset_location;  //Just the offset location in first block. Needs updation when data spans multiple blocks. 
	int number_of_blocks;
	int current_size;
	struct object* prev;
	struct object* next;
}object;

//Using #defines along with the structures
#define PENDING   0
#define COMMITTED 1
#define ABORTED   2
typedef struct
{
	long int id;
	int status; // Can be one of the above mentioned identifiers
}transaction_identifier;

typedef struct table_obj_id
{
	struct table_obj_id* next;
	int id;
	long int offset;
}table_obj_id;
//Since the starting offset is known, iterating with number of elements should give us the element we need
typedef struct
{
	int elements;
	long int offset;
	table_obj_id* list;
}object_table;

//Global variables
FILE *fp_cell_storage_system;
FILE *fp_log_file;

/************Extern functions**********************/
//System functions
extern int bootup();
extern int user_applications();
extern transaction_identifier* begin_transaction();


//Logging functions
extern void LOG(int string, ...);

//Cell storage functions
extern object * create_new_object(char * var_name, int value);
extern void free_object(object *id);

extern object* allocate(char* name, int value);
extern int init_cell_storage();

extern void write(object* node, int overwrite_flag);
extern void insert(object_table **table, object *new_obj);
extern void insert_table_obj_list_to_table(object_table **table, table_obj_id **objid);
extern int search(object_table*table, int id);

extern void PUT(object* ref_id, int value);
extern void write_table_to_file(object_table *table);

extern object_table * read();
extern int GET(object* ref_id, transaction_identifier* my_id);

extern void deallocate(object *obj);
extern object_table * delete_obj_id(object_table **table, object **obj_id);
//User applications

#endif
