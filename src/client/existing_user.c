/******************************************************************************
*
*  FILE NAME   : existing_user.c
*
*  DESCRIPTION : This function is for existing user login that
*		 calls the other following functions :
*			1. get_login_details
*			2. send_to_server
*			3. recv_from_server
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat		Nalanda Project
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
 *	FUNCTION NAME	: existing_user_processing
 *
 *	DESCRIPTION	: This function is for existing user login that
 *			  calls the other following functions :
 *			  1. get_login_details
 *			  2. send_to_server
 *			  3. recv_from_server
 *
 *	RETURNS 	: SUCCESS or FAILURE
 *
*******************************************************************************/

int existing_user_processing(
			int socket_fd, 		/* for socket fd */
			char *send_buf, 	/* send buffer that stores login details of Client */
			char *recv_buf)		/* recv buffer that stores message sent by Server */
{

	log_client_report(NORMAL, "Entering : Existing_user_processing", __FILE__, __LINE__);				//writing to the output log file
	int status = 0;
	pthread_t tid1, tid2;
	void *send_ret_val = NULL;									//pointer to store the return value of thread.
	void *recv_ret_val = NULL;

	status = get_login_details(send_buf);							/* calling the get_login_detail function 
							  					   		to get login and password from Client */
		
	if (status == SUCCESS)									//Validating the get_login_details function
	{
		encrypt(send_buf);									//encrypting user id and password before sending
		
		printf("\n\tEncrypted userid:pass is = %s\n\n", send_buf);

		status = send_to_server(socket_fd, send_buf);					/* Calling the send_to_server function 
							   			   		   		to send login and password to Server */
			
		if (status == SUCCESS)								//Validating the send_to_server function
		{
			printf ("\n\tLogin details send to Server Successfully\n\n");
					
			status = recv_from_server(socket_fd, recv_buf);				/* Calling the recv_from_server function 
							   			   	  	   		to receive the message from Server */

			if (status == SUCCESS)							//Validating the recv_from_server function
			{
				if (strcmp(recv_buf, "Wrong credentials") == 0)			
				{
					printf ("\n\tMsg from server = %s\n\n", recv_buf);	//printing the message sent by Server
					memset(recv_buf, '\0', strlen(recv_buf));			//flushing the recv_buf for reuse

					close(socket_fd);						//closing the socket_fd
					exit(EXIT_FAILURE);
				}
				else
				{
					printf ("\n\tMsg from server = %s\n\n", recv_buf);	//printing the message sent by Server
					memset(recv_buf, '\0', strlen(recv_buf));			//flushing the recv_buf for reuse
				
					status = -1;
					status = pthread_create(&tid1, NULL, brdcst_recv_handler, (void *)&socket_fd);		// Creating the receive message thread.
					if(status < 0)
					{
						perror("\n\tUnable to create the receiving thread ");
					 
						close(socket_fd);										//closing the socket_fd
						exit(EXIT_FAILURE);
					}

						
					status = -1;
					status = pthread_create(&tid2, NULL, brdcst_send_handler, (void *)&socket_fd);		// Creating the send message thread.
					if(status < 0)
					{
						perror("\n\tUnable to create the sending thread ");
					 
						close(socket_fd);										//closing the socket_fd
						exit(EXIT_FAILURE);
					}
	
					/*
					* now waiting for recv broadcast thread to complete 
					*/

					status = -1;
					status = pthread_join(tid1, &recv_ret_val); 						//waits for thread - tid1 to return recv_ret_val pointer
					if (-1 == status)
					{
						printf("\n\tUnable to join the brdcst_recv thread \n");
						perror("Broadcast recv Thread ");
					 
						close(socket_fd);									//closing the socket_fd
						exit(EXIT_FAILURE);					
					}
					else if (recv_ret_val != NULL)
					{
						printf("\n\trecv thread msg : Client has loged out \n\n");
						//pthread_kill(tid1, SIGKILL);
						
					}

					/*
					* now waiting for send broadcast thread to complete 
					*/

					status = -1;
					status = pthread_join(tid2, &send_ret_val); 						//waits for thread - tid2 to return recv_ret_val pointer
					if (-1 == status)
					{
						printf("\n\tUnable to join the brdcst_send thread \n");
						perror("Broadcast send Thread ");
					 
						close(socket_fd);									//closing the socket_fd
						exit(EXIT_FAILURE);					
					}
					else if (send_ret_val != NULL)
					{
						printf("\n\tsend thread msg : Client has loged out \n\n");
						//pthread_kill(tid2, SIGKILL);
					}

					return SUCCESS;

				}
		
			}	
			else
			{
				log_client_report(ERROR, "ERROR : Error in recieving Message from Server", __FILE__, __LINE__);			//writing the error message to output log file
				printf ("\n\tError in Receiving Message from Server....\n\n");					//printing the error message
				
				return FAILURE;
			}
		}
		else
		{
			log_client_report(ERROR, "Error in sending Detail to server", __FILE__, __LINE__);						//writing the error message to output log file
			printf ("\n\tError in sending details to Server \n\n");							//printing the error message

			return FAILURE;			
		}
	}
	else
	{
		log_client_report(ERROR, "ERROR : Error in getting Login Details....", __FILE__, __LINE__);					//writing the error message to output log file
		printf ("\n\tError in getting Login Details.........\n\n");							//printing the error message

		return FAILURE;		
	}
	log_client_report(NORMAL, "Exiting : User_processing", __FILE__, __LINE__);									//writing to output log file
	return SUCCESS;														//returning SUCCESS status to calling function
}
