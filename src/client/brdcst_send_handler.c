/******************************************************************************
*
*  FILE NAME   : brdcst_send_handler.c
*
*  DESCRIPTION : it includes start routine function for broadcast send thread 
*		 to handle the sending broadcast message processing
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
 * FUNCTION NAME : brdcst_send_handler
 *
 * DESCRIPTION   : this is start routine function for broadcast send thread
 * 	
 * RETURNS	   : retuns nothing but exit thread at end
 
*******************************************************************************/

void *brdcst_send_handler(void *sockfd)
{
	log_client_report(NORMAL, "Entering : brdcst_send_handler", __FILE__, __LINE__);						//Writing in output log file
	printf("\n\tNew Send Broadcast thread started with thread id = %ld\n\n", pthread_self());		//printing the thread id

	printf("\n\tStart chat now...\n\n");

	int socket_fd = *((int *)sockfd);
	int status = -1;

	char send_buf[BUFFER_SIZE] = {'\0'};

	while (1)
	{
		memset(&send_buf, '\0', sizeof(send_buf));							//flushing buf for reusing later

		printf("\n\tyou > ");

		getchar();
		scanf("%[^\n]", send_buf);										//getting the message from client that needs to be broadcasted
	
		status = -1;
		status = send_to_server(socket_fd, send_buf);							//calling this function to send the data to Server
		if (status == FAILURE)										//validating the send_to_server function
		{
			log_client_report(ERROR, "ERROR : in broadcast send thread", __FILE__, __LINE__);				//Writing the error message in output log file
			perror("\n\tError : in broadcast send thread ");
			break;
		}

		if (!strcmp(send_buf, LOGOUT))									//comparing whether the message typed by client not the BYEBYE
		{
			printf("\n\tSend Broadcast thread done with thread id = %ld\n\n", pthread_self());	//printing the thread id
			pthread_exit((void*)LOGOUT);								//Exiting the thread
		}
	}

	printf("\n\tSend Broadcast thread done with thread id = %ld\n\n", pthread_self());			//printing the thread id
	log_client_report(NORMAL, "Exiting : brdcst_send_handler", __FILE__, __LINE__);							//Writing the error message in output log file
	pthread_exit(NULL);												//Exiting the thread
}