/*********************************************************************************
*
*  FILE NAME   : new_user_processing.c
*
*  DESCRIPTION : it include funtion that does the pocessing for new client
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
**********************************************************************************/

#include <server_util.h>			//contails all macros and header files
#include <common_crypto.h>			//contails all cryptograpy functions

/*********************************************************************************
 * FUNCTION NAME : new_user_processing
 *
 * DESCRIPTION   : this funtion does the pocessing for new client
 * 	
 * RETURNS	   : retuns SUCCESS or FAILURE
 
**********************************************************************************/

int new_user_processing(
			pthread_mutex_t *file_mutex,		/* To store file_mutex */
			GSList **list,				/* To store active_client_list address */
			int connfd,					/* for client connfd */
			char *recv_buf, 				/* for recving buf ptr */
			char *send_buf)				/* for sending buf ptr */
{

	log_server_report(NORMAL, "Entering : new_user_processing", __FILE__, __LINE__);
	int ret_val = -1;

	//receiving new userid & pass from client to be stored
	ret_val = recv_from_client(connfd, recv_buf);
	decrypt(recv_buf);
	if (SUCCESS == ret_val)
	{
		//checking if the userid already exits 
		ret_val = -1;
		ret_val = is_user_exist(recv_buf);
		if (SUCCESS == ret_val)
		{
			printf("\n\tUser already Exists !!\n\n");
	
			//sending user exist msg to client
			ret_val = -1;
			strcpy(send_buf, "User Already Exists");
			ret_val = send_to_client(connfd, send_buf);
			if (SUCCESS == ret_val)
			{
				printf("\n\tUser exists msg send to client !!\n\n");
				
				//flushing buf to be reuse
				memset(recv_buf, '\0', strlen(recv_buf));
				
				return FAILURE;
			}
			else
			{

				log_server_report(ERROR, "ERROR : new_user_processing", __FILE__, __LINE__);
				printf("\n\tError in sending exists user msg !!\n\n");
				return FAILURE;	
			}
		}
		else if (FAILURE == ret_val)
		{
			
			printf("\n\tIt is a New User adding userid pass to reg user file !!\n\n");
			
			//adding to reg usres file by calling function with locks
			ret_val = -1;
			pthread_mutex_lock(file_mutex);
			ret_val = add_to_reg_user_file(recv_buf);		
			pthread_mutex_unlock(file_mutex);
			if (SUCCESS == ret_val)
			{
				printf("\n\tLogin Credentials added to reg_user file Successfully\n");
				
				//flushing buf to be reuse
				memset(recv_buf, '\0', strlen(recv_buf));

				//sending user reg success msg to client
				ret_val = -1;
				strcpy(send_buf, "Registed Successfully");
				ret_val = send_to_client(connfd, send_buf);
				if (SUCCESS == ret_val)
				{
					printf("\n\tUser reg success msg send to client !!\n\n");

					log_server_report(NORMAL, "Exiting : new_user_processing", __FILE__, __LINE__);

					return SUCCESS;
				}
				else
				{
					log_server_report(ERROR, "ERROR : new_user_processing", __FILE__, __LINE__);
					printf("\n\tError in sending user reg success msg !!\n\n");
					return FAILURE;	
				}	
				
			}
			else
			{
				log_server_report(ERROR, "ERROR : new_user_processing", __FILE__, __LINE__);
				printf("\n\tError in appending data to reg_user file\n");		
				return FAILURE;
			}	
		}
	
	}
	else	
	{
		printf("\n\tNo new credentials received from client !!\n\n");
		log_server_report(ERROR, "ERROR : No new credentails received from client", __FILE__, __LINE__);
		return FAILURE;
	}

	//log_server_report(NORMAL, "Exiting : new_user_processing", __FILE__, __LINE__);

	return FAILURE;

}