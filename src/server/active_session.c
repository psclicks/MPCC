/*********************************************************************************
*
*  FILE NAME   : active_session.c
*
*  DESCRIPTION : it include all utility functions to maintain the active clients sessions.
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
**********************************************************************************/

/******************************************************************************
 *	ALL NECESSARY COMMON HEADERS, MACROS AND FUNCTIONS FOR CLIENT PROGRAM
*******************************************************************************/

#include <server_util.h>			

/*********************************************************************************
 * FUNCTION NAME : add_to_active_client_list
 *
 * DESCRIPTION   : this funtion adds the authenticated client to active_client_list
 * 	
 * RETURNS	   : retuns SUCCESS or FAILURE
 
**********************************************************************************/
int add_to_active_client_list(
				GSList **list,		/* To store active_client_list address */
				int connfd,			/* to store connfd of auth client */
				char *auth_userid)		/* to store addr of auth_userid */
{
	log_server_report(NORMAL, "Entering : add_to_active_client_list function ", __FILE__, __LINE__);			//writing to the output log file
	
	ACTIVE_CLIENT *active_client = NULL;
	memset(&active_client, 0, sizeof(active_client));									//to initializing the structure with NULL

	active_client = (ACTIVE_CLIENT*) malloc(sizeof(ACTIVE_CLIENT));							//allocating memory for ACTIVE_CLIENT structure
	if (!active_client)
	{	
		perror("\n\tMALLOC ERROR :In add_to_client ");
		log_server_report(ERROR, "ERROR : in add_to_active_client", __FILE__, __LINE__);				//writing the error message to log file
		return FAILURE;
	}
	else
	{
		memset(active_client, 0, sizeof(ACTIVE_CLIENT));									//initializing the structure with 0

		active_client->connfd = connfd;
		active_client->userid = auth_userid;

		if ((!active_client->connfd) || (!active_client->userid))
		{
			log_server_report(ERROR, "ERROR : in add_to_active_client", __FILE__, __LINE__);			//writing the error message to log file
			printf("\n\tError : Some data before list append is NULL !!\n\n");
			return FAILURE;		
		}
		else
		{
			*list = g_slist_append(*list, (gpointer) active_client);						// This is a list of active authenticated clients
		
			return SUCCESS;
		}
	}
	
	log_server_report(NORMAL,"Exiting : add_to_active_client_list function", __FILE__, __LINE__);				//writing to the log file

}


/*********************************************************************************
 * FUNCTION NAME : remove_from_active_client_list
 *
 * DESCRIPTION   : this funtion removes client data from active_client_list
 * 	
 * RETURNS	   : retuns SUCCESS or FAILURE
 
**********************************************************************************/
int remove_from_active_client_list(
				GSList **list,		/* To store active_client_list address */
				int connfd)			/* to store connfd of auth client */
{
	GSList *get_node = NULL;

	log_server_report(NORMAL, "Entering : remove_from_active_client_list function ", __FILE__, __LINE__);			//writing to the output log file

	if (!*list)
	{
		log_server_report(ERROR, "ERROR : in remove_from_client_list", __FILE__, __LINE__);				//writing the error message to log file			
		printf("\n\tList is Empty can't remove client !!\n\n");
		return FAILURE;
	}
	else
	{
		get_node = g_slist_find_custom(*list, &connfd, (GCompareFunc)find_client);		/*find_client is the function to call for each element. 
												 		It should return 0 when the desired client is found */				
		if (!get_node)
		{
			printf("\n\tConnfd not found in list !!\n\n");
			log_server_report(ERROR, "ERROR : Connfd not found", __FILE__, __LINE__);
			return FAILURE;						
		}
		else
		{
			free_func(get_node->data);								//functon to free node memory
			
			*list = g_slist_delete_link(*list, get_node);

			log_server_report(NORMAL, "Exiting : remove_from_active_client_list function", __FILE__, __LINE__);

			return SUCCESS;												
		}
		
	}
							

}