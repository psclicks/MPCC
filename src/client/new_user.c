/******************************************************************************
*
*  FILE NAME    : new_user.c
*
*  DESCRIPTION  : it include funtion that does the pocessing for new client		  		    
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

#include <client_util.h>				
#include <common_crypto.h>			

/******************************************************************************
 *	FUNCTION NAME	: new_user_processing
 *
 *	DESCRIPTION	: This function is for new user registration that
 *			  calls the other following functions :
 *			  1. get_login_details
 *			  2. send_to_server
 *			  3. recv_from_server
 *			  4. existing_user_processing
 *
 *	RETURNS 	: SUCCESS or FAILURE
 *
*******************************************************************************/

int new_user_processing(
		int socket_fd,		/* for socket fd */ 
		char *send_buf, 		/* send buffer that stores login details of Client */
		char *recv_buf)		/* recv buffer that stores message sent by Server */
{
	log_client_report(NORMAL, "Entering : New_User_Processing", __FILE__, __LINE__);
	int status = 0;
	
	status = get_login_details(send_buf);											/* calling the get_login_detail function 
							   										to get login and password from Client */

	if (status == SUCCESS)													//Validating the get_login_details function
	{
		encrypt(send_buf);		//encrypting userid pass before sending

		status = send_to_server(socket_fd, send_buf);									/* Calling the send_to_server function 
							   			   							to send login and password to Server */

		if (status == SUCCESS)												//Validating the send_to_server function
		{
			printf ("\n\tLogin details send to Server Successfully\n\n");
					
			status = recv_from_server(socket_fd, recv_buf);								/* Calling the recv_from_server function 
							   			   	   						to receive the message from Server */
						
			if (status == SUCCESS)											//Validating the send_to_server function
			{
				if (strcmp(recv_buf, "User Already Exists") == 0)
				{
					printf ("\n\tMsg from server = %s\n\n", recv_buf);					//printing the message sent by Server

					exit(EXIT_FAILURE);
				}
				else
				{
					printf ("\n\tMsg from server = %s\n\n", recv_buf);					//printing the message sent by Server
				
					memset(send_buf, '\0', strlen(send_buf));							//flushing the send_buf for reuse
					memset(recv_buf, '\0', strlen(recv_buf));

					status = existing_user_processing(socket_fd, send_buf, recv_buf);			/* Calling the existing_user_processing 
														  		 	function to get the login details again
														  		 	to send message in conference chat room */

					if (status == FAILURE)									//Validating the send_to_server function
					{
						printf ("\n\tError in calling Existing_User_Processing function......\n\n");	//printing the error message

						return FAILURE;					
					}
				}

				memset(recv_buf, '\0', strlen(recv_buf));								//flushing the recv_buf for reuse
		
			}
			else
			{
				log_client_report(ERROR, "ERROR : Error receiving Message", __FILE__, __LINE__);					//writing the error message to output log file
				printf ("\n\tError in Receiving Message from Server....\n\n");					//printing the error message
				
				return FAILURE;
			}
		}
		else
		{
			log_client_report(ERROR, "ERROR : Error in Sending Details", __FILE__, __LINE__);						//writing the error message to output log file
			printf ("\n\tError in sending details to Server\n\n");							//printing the error message
			
			return FAILURE;
		}
	}
	else
	{
		log_client_report(ERROR, "ERROR : Error in getting Details", __FILE__, __LINE__);							//writing the error message to output log file
		printf ("\n\tError in getting Login Details.........\n\n");							//printing the error message
		
		return FAILURE;		
	}
	log_client_report(NORMAL, "Exiting : New_User_Processing", __FILE__, __LINE__);									//writing to the output log file
	return SUCCESS;														//returning SUCCESS status to calling function
}