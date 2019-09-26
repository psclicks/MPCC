/******************************************************************************
*
*  FILE NAME   : log_server_report.c
*
*  DESCRIPTION : this file contails function to generate log report file for server
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
*******************************************************************************/

/******************************************************************************
 *	ALL NECESSARY COMMON HEADERS, MACROS AND FUNCTIONS FOR CLIENT PROGRAM
*******************************************************************************/

#include <server_util.h>			

/******************************************************************************
 *	FUNCTION NAME	: log_server_report.
 *
 *	DESCRIPTION	: function to generate log report file for server
 *
 *	RETURNS 	: nothing

*******************************************************************************/

void log_server_report( 
				int type,		/* log level */
				char *msg,		/* buffer ptr that stores the data */
				char *file,		/* buffer ptr that stores the file path */
				int line)		/* for line no*/
{
	FILE *append_fp = NULL;

	append_fp = fopen(LOGPATH, "a");						//opening the log file where to write			

	if (!append_fp)								//validation then proceeding
	{
		printf("\n\tERROR : While opening log file !!\n\n");
		return;
	}
	else
	{
		if (ERROR == type)
		{
			fprintf(append_fp, "%s in file %s at line %d\n", msg, file, line);	
		}
		else
		{
			fprintf(append_fp, "%s\n", msg);			
		}
	 
		fclose(append_fp);							//closing the file				
	}
}

