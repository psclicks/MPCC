/*********************************************************************************
*
*  FILE NAME   : send_recv.c
*
*  DESCRIPTION : it include functions to send recv data from/to client
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
**********************************************************************************/

#include <server_util.h>			//contails all macros and header files

/*********************************************************************************
 *	FUNCTION NAME	: send_to_client
 *
 *	DESCRIPTION	: function to send data to the connected client
 *
 *	RETURNS 	: SUCCESS or FAILURE

**********************************************************************************/
int send_to_client(
			int connfd,		/* for socket fd */
			char *buf)		/* for src buffer */
{
	int ret_val = -1;

	log_server_report(NORMAL, "Entering : send_to_client", __FILE__, __LINE__);

	ret_val = send(connfd, buf, (strlen(buf)+1), 0);
	if ((-1 == ret_val) || (ret_val > (strlen(buf)+1)))
	{

		log_server_report(ERROR, "ERROR : send_to_client", __FILE__, __LINE__);
		perror("\n\tERROR : in send_to_client ");

		return FAILURE;
	}
	if ((ret_val > 0) && (ret_val == (strlen(buf)+1)))
	{
		//printf("\n\t%d bytes send to client with msg = %s\n\n", ret_val, buf);

		//flushing buf to be reuse
		//memset(buf, '\0', strlen(buf));

		log_server_report(NORMAL, "Exiting : send_to_client", __FILE__, __LINE__);
		
		return SUCCESS;
	}
	if (0 == ret_val)
	{
		printf("\n\tNo data send to client !!\n\n");

		log_server_report(ERROR, "ERROR : no_data_send_to_client", __FILE__, __LINE__);

		return FAILURE;
	}
	
	return FAILURE;	
} 
 
/*********************************************************************************
 *	FUNCTION NAME	: recv_from_client
 *
 *	DESCRIPTION	: function to recv data from the connected client
 *
 *	RETURNS 	: SUCCESS or FAILURE

**********************************************************************************/
int recv_from_client(
			int connfd,		/* for socket fd */
			char *buf)		/* for dest buffer */
{
	int ret_val = -1;
	
	log_server_report(NORMAL, "Entering : recv_from_client", __FILE__, __LINE__);
	ret_val = recv(connfd, buf, MAX_SIZE, 0);
	if ((-1 == ret_val) || (ret_val > MAX_SIZE))
	{
		perror("\n\tERROR : in recv_from_client ");

		return FAILURE;
	}
	if ((ret_val > 0) && (ret_val == (strlen(buf)+1)))
	{
		//printf("\n\t%d bytes received from client with msg = %s \n\n", ret_val, buf);

		log_server_report(NORMAL, "Exiting : recv_from_client", __FILE__, __LINE__);
		
		return SUCCESS;
	}
	if (0 == ret_val)
	{
		printf("\n\tNo data received from client !!\n\n");

		log_server_report(ERROR, "ERROR : no _data_receive from_client", __FILE__, __LINE__);


		return FAILURE;
	}

	return FAILURE;	
}










	


