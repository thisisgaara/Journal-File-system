/***********************************************************************************
* 		Name: main.c
*		Purpose: Nothing to see here. Just calls to bootup and call test application.
*		Author: Vignesh Kannan
*		Version: 0.1
*		Date:03/23/2016
************************************************************************************/
#include "header.h"
long int trans_id;
int main(int argc, char** argv)
{
	trans_id = 0; //Initialize transaction identifier
	//Creating the cell storage system
	//Open with write+ so that the entire file is persistent during system reboot.
	fp_cell_storage_system = fopen(NAME_OF_CELL_STORAGE_SYSTEM, "wb");
	init_cell_storage();
    bootup();

	//Delegating control to user
    user_applications();
	return 0;
}
