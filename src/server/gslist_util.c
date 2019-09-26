/*********************************************************************************
*
*  FILE NAME   : gslist_util.c
*
*  DESCRIPTION : it include all utility functions required by the gslist.
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
**********************************************************************************/

#include <server_util.h>			//contails all macros and header files

/*********************************************************************************
 * FUNCTION NAME : free_func
 *
 * DESCRIPTION   : callback function to free each node data of gslist
 * 	
 * RETURNS	   : none
 
**********************************************************************************/

void free_func(gpointer data)
{

	if (((ACTIVE_CLIENT*)data)->userid != NULL)	
	{
		FREE(((ACTIVE_CLIENT*)data)->userid);
		
	}

	if (data != NULL)
	{
		FREE(data);		
	}				
}

/*********************************************************************************
 * FUNCTION NAME : display_list
 *
 * DESCRIPTION   : callback function to display list data
 * 	
 * RETURNS	   : none
 
**********************************************************************************/

void display_list(gpointer data, gpointer user_data)
{
	if(!data)
	{
		printf("\n\tLink List Data Ptr content is NULL\n\n");
	}
	else
	{
		printf("\n\tCONNFD   : %d\n", ((ACTIVE_CLIENT*)data)->connfd );
		printf("\n\tUSERID 	: %s\n", ((ACTIVE_CLIENT*)data)->userid );
	}
	
}

/*********************************************************************************
 * FUNCTION NAME : find_client
 *
 * DESCRIPTION   : callback function to be find client for each list node
 * 	
 * RETURNS	   : difference between node data1 and passed data2
 
**********************************************************************************/

gint find_client(gconstpointer data1, gconstpointer data2)
{
	return ( ((ACTIVE_CLIENT*)data1)->connfd - *(int*)data2);
}