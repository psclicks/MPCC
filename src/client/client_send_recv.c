/******************************************************************************
*
*  FILE NAME    : client_send_recv.c
*
*  DESCRIPTION  : This file contains definition of following functions :
*		    1. send_to_server : This function sends data to Server
*
*		    2. recv_from_server : This function receive the data send 
*					     by Server 		  		    
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
				  
/******************************************************************************
 *	FUNCTION NAME	: send_to_server
 *
 *	DESCRIPTION	: function to send data to the connected Server
 *
 *	RETURNS 	: SUCCESS or FAILURE
 *
*******************************************************************************/

int send_to_server(	
		int socket_fd,		/* for socket fd */
		char *send_buf)		/* for send buffer that containing login details */
{

	log_client_report(NORMAL, "Entering : Send_to_server", __FILE__, __LINE__);					//writing to output log file
	int send_num = -1;

	send_num = send(socket_fd, send_buf, (strlen(send_buf) + 1), 0);			/* Calling send function to
										   		   		send details to server */

	//printf ("\n\t%d bytes sent to Server with msg = %s\n\n", send_num, send_buf);

	if ((-1 == send_num) || (send_num > (strlen(send_buf) + 1)))				//validating the number of bytes sent
	{
		perror("\n\tERROR : in send_to_client ");						//printing the error message

		log_client_report(ERROR, "Error : in_send to client", __FILE__, __LINE__);
		
		return FAILURE;		
	}
	if (send_num < strlen(send_buf))								//validating the number of bytes sent
	{	
		printf ("\n\tLess bytes are send to Server \n\n");				//printing the error message

		log_client_report(ERROR, "Error : Less bytes are send to server", __FILE__, __LINE__);

		return FAILURE;
	}
	if (0 == send_num)										//validating the number of bytes sent
	{
		printf("\n\tNo data send to Server !!\n\n");					//printing the error message

		log_client_report(ERROR, "Error : No data send to server", __FILE__, __LINE__);
		
		return FAILURE;
	}
	
	log_client_report(NORMAL, "Exiting : Send_to_server", __FILE__, __LINE__);					//writing the errror message to the output log file					

	return SUCCESS;										//returning SUCCESS status to calling function
}  
 
/******************************************************************************
 *	FUNCTION NAME	: recv_from_server
 *
 *	DESCRIPTION	: function to receive message sent by connected Server
 *
 *	RETURNS 	: SUCCESS or FAILURE
 *
*******************************************************************************/

int recv_from_server( 
		int socket_fd,		/* for socket fd */
		char *recv_buf )	/* for recv buffer that containing message send by server */
{
	log_client_report(NORMAL, "Entering : recv_from_server", __FILE__, __LINE__);					//writing to output log file
	int recv_num = -1;

	recv_num = recv(socket_fd, recv_buf, BUFFER_SIZE, 0);				/* Calling recv function to
									   		   		recv message from server */
	if ((-1 == recv_num) || (recv_num > BUFFER_SIZE))
	{
		perror("\n\tERROR : in recv_from_Server ");				//printing the error message

		log_client_report(ERROR, "ERROR : in recv_from_Server", __FILE__, __LINE__);
		
		return FAILURE;
	}
	if (0 == recv_num)									//validating the number of bytes received
	{
		printf("\n\tNo data receive from Server !!\n\n");			//printing the error message

		log_client_report(ERROR, "Error : No data receive from Server", __FILE__, __LINE__);
			
		return FAILURE;
	}

	log_client_report(NORMAL, "Exiting : recv_from_server", __FILE__, __LINE__);					//writing the errror message to the output log file
	return SUCCESS;									//returning SUCCESS status to calling function
}	
