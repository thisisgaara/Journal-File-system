/************************************************************************************
*		Name: bootup.c
*		Purpose: Demarcates the cell storage system and returns file offsets
for various locations in cell storage system
Author: Vignesh Kannan
Date: 03/23/2016
Version: 0.1
**************************************************************************************/
#include "header.h"
int bootup()
{
	//Creating log file
	//Using a+ mode during creation so that, if log doesnot exist, create it. IN case of recovery, open exising log for reading. 
	fp_log_file = fopen(LOG_FILE, "a+");
	fclose(fp_log_file);

	return 0; //Success
}


