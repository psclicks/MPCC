/******************************************************************************
*
*  FILE NAME   : brdcst_recv_handler.c
*
*  DESCRIPTION : it includes start routine function for broadcast recv thread
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
 * FUNCTION NAME : brdcst_recv_handler
 *
 * DESCRIPTION   : this is start routine function for broadcast recv thread
 * 	
 * RETURNS	 : retuns nothing but exit thread at end
 
*******************************************************************************/

void *brdcst_recv_handler(void *sockfd)
{
	log_client_report(NORMAL, "Entering : brdcst_recv_handler", __FILE__, __LINE__);					//Writing in output log file
	printf("\n\tNew Recv Broadcast thread started with thread id = %ld\n\n", pthread_self());	//printing the thread id

	int socket_fd = *((int *)sockfd);
	int status = -1;
	char *userid = NULL;
	char *msg = NULL;

	char recv_buf[BUFFER_SIZE] = {'\0'};
		
	while (1)
	{	
		status = -1;
		status = recv_from_server(socket_fd, recv_buf);						//calling this function to get receiving data from server
		if (status == FAILURE)									//validating recv_from_server functtion
		{
			printf("\n\tRecv Broadcast thread done with thread id = %ld\n\n", pthread_self());	//printing the thread id
			pthread_exit((void*)LOGOUT);
		}

		userid = strtok(recv_buf, DELIMITER);							//getting received userid 
		msg = strtok(NULL, DELIMITER);								//getting received message

		printf("\n\t%s > %s\n", userid, msg);

		fflush(stdout);

		memset(&recv_buf, '\0', sizeof(recv_buf));						//flushing buf for reusing later		
		
	}
	
	printf("\n\tRecv Broadcast thread done with thread id = %ld\n\n", pthread_self());
	log_client_report(NORMAL, "Exiting : brdcst_recv_handler", __FILE__, __LINE__);						//Writing the error message in output log file
	pthread_exit(NULL);											//Exiting the thread
}