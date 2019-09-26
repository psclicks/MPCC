/*********************************************************************************
*
*  FILE NAME   : existing_user_processing.c
*
*  DESCRIPTION : it include funtion that does the pocessing for existing client
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
**********************************************************************************/

#include <server_util.h>			//contails all macros and header files
#include <common_crypto.h>			//contails all cryptograpy functions

//#define STUB_AUTHENTICATE

/*********************************************************************************
 * FUNCTION NAME : existing_user_processing
 *
 * DESCRIPTION   : this funtion does the pocessing for existing client
 * 	
 * RETURNS	   : retuns SUCCESS or FAILURE
 
**********************************************************************************/

int existing_user_processing(
				pthread_mutex_t *list_mutex,		/* To store list_mutex addr */
				GSList **list,				/* To store active_client_list address */
				int connfd,					/* for client connfd */
				char *recv_buf, 				/* for recving buf ptr */
				char *send_buf)				/* for sending buf ptr */
{
	int ret_val = -1;
	char *auth_userid = NULL;

	log_server_report(NORMAL, "Entering : existing_user_processing", __FILE__, __LINE__);

	//receiving userid & pass from client
	ret_val = recv_from_client(connfd, recv_buf);
	
	printf("\n\tEncrypted userid:pass received is = %s\n\n", recv_buf);

	decrypt(recv_buf);

	if (SUCCESS == ret_val)
	{
		#ifndef STUB_AUTHENTICATE

		auth_userid = stub_authenticate();

		#else
		
		//authenticating user now
		auth_userid = client_authentication(recv_buf);

		#endif

		if (!auth_userid)
		{	
			printf("\n\tWrong credentials | Not a valid user !!\n\n");

			//sending wrong credential msg to client
			ret_val = -1;
			strcpy(send_buf, "Wrong credentials");
			ret_val = send_to_client(connfd, send_buf);
			if (SUCCESS == ret_val)
			{
				printf("\n\tWrong credentials msg send to client !!\n\n");

				//flushing buf to be reuse
				memset(recv_buf, '\0', strlen(recv_buf));

				return FAILURE;
			}
			else
			{
				log_server_report(ERROR, "ERROR : existing_user_processing", __FILE__, __LINE__);

				printf("\n\tError in sending wrong credentials msg !!\n\n");

				return FAILURE;	
			}
	
		}
		else
		{
			printf("\n\tClient Successfully Authenticated !!\n\n");

			//adding to active authenticated client list with locks
			ret_val = -1;
			pthread_mutex_lock(list_mutex);
			ret_val = add_to_active_client_list(list, connfd, auth_userid);		
			pthread_mutex_unlock(list_mutex);
			if (SUCCESS == ret_val)
			{
				printf("\n\tSuccessfully added to active client list !!\n\n");
		
			}
			else
			{
				log_server_report(ERROR, "ERROR : existing_user_processing", __FILE__, __LINE__);

				printf("\n\tError in adding to active client list !!\n\n");	
			}	
	
	
			//sending welcom msg to client
			ret_val = -1;
			strcpy(send_buf, "Login Successfull");
			ret_val = send_to_client(connfd, send_buf);
			if (SUCCESS == ret_val)
			{
				printf("\n\tLogin msg send to client !!\n\n");

				//flushing buf to be reuse
				memset(recv_buf, '\0', strlen(recv_buf));

				log_server_report(NORMAL, "Exiting : Exiting_user_processing", __FILE__, __LINE__);

				return SUCCESS;

			}
			else
			{
				printf("\n\tError in sending wlcom msg !!\n\n");

				//removing this client from active client list
				ret_val = -1;
				ret_val = remove_from_active_client_list(list, connfd);
				if (SUCCESS == ret_val)
				{
					printf("\n\tSuccessfully removed from active client list !!\n\n");		
				}
				else
				{
					printf("\n\tError removing from active client list !!\n\n");	
				}

				log_server_report(ERROR, "ERROR : Error in removing active client list", __FILE__, __LINE__);

				return FAILURE;	
			}	

		}
	}
	else	
	{
		log_server_report(ERROR, "ERROR : existing_user_processing", __FILE__, __LINE__);

		printf("\n\tNo data (credentials) received from client !!\n\n");
		return FAILURE;
	}
	
	

}