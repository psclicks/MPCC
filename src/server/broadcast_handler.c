/*********************************************************************************
*
*  FILE NAME   : broadcast_handler.c
*
*  DESCRIPTION : it include is start routine function for broadcast thread
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
**********************************************************************************/

#include <server_util.h>			//contails all macros and header files

/*********************************************************************************
 * FUNCTION NAME : broadcast_handler
 *
 * DESCRIPTION   : this is start routine function for broadcast thread 
 * 	
 * RETURNS	   : retuns nothing but exit thread at end
 
**********************************************************************************/

void *broadcast_handler(
		void *brd_th_data)	/* BRD_TH_DATA obj is passed as the arg */
{

	log_server_report(NORMAL, "Starting : broadcast_handler thread", __FILE__, __LINE__);
	printf("\n\tNew Broadcast thread started with thread id = %ld\n\n", pthread_self());

	/******Initialization**********/

	BRD_TH_DATA *brd_thread_data = (BRD_TH_DATA*)brd_th_data;
	int connfd = brd_thread_data->clientfd;				 
	GSList **list = brd_thread_data->list;
	GSList *iterator = NULL;

	int ret_val = -1;			
	char brdcst_recv_buf[MAX_SIZE] = {'\0'};
	char brdcst_send_buf[MAX_SIZE] = {'\0'};

	/******Reading from client and writing it to all other active clients**********/
	
	while (1)
	{
		//receiving broadcast msg from client
		ret_val = -1;
		ret_val = recv_from_client(connfd, brdcst_recv_buf);
		if (SUCCESS == ret_val)
		{
			
			if (!strcmp(brdcst_recv_buf, "byebye"))
			{
				break;
			}	
		
			//retriving userid from list
			for (iterator = *list; iterator; iterator = iterator->next)
			{
				if (connfd == ((ACTIVE_CLIENT*)(iterator->data))->connfd)
				{
					strcpy(brdcst_send_buf, (((ACTIVE_CLIENT*)(iterator->data))->userid));
					strcat(brdcst_send_buf, DELIMITER);
					strcat(brdcst_send_buf, brdcst_recv_buf);

					break;
				}
				else
				{
					continue;
				}
			}

			//Send broadcast msg to clients
			for (iterator = *list; iterator; iterator = iterator->next)
			{
				if (connfd == ((ACTIVE_CLIENT*)(iterator->data))->connfd)
				{
					continue;
				}
				else
				{
					ret_val = -1;
					ret_val = send_to_client((((ACTIVE_CLIENT*)(iterator->data))->connfd), brdcst_send_buf);
					if (SUCCESS == ret_val)
					{
						printf("\n\tBroadcast msg send to < %s > !!\n\n", (((ACTIVE_CLIENT*)(iterator->data))->userid));
					}
					else
					{
						printf("\n\tError in sending broadcast msg !!\n\n");
						break;	
					}
				}
	
			}
		}
		else
		{
			log_server_report(ERROR, "ERROR : Error in BroadCasting Message", __FILE__, __LINE__);
			printf("\n\tError in receving broadcast msg !!\n\n");
			break;
		}
	
		//flushing buf for reusing later
		memset(&brdcst_send_buf, '\0', sizeof(brdcst_send_buf));
		memset(&brdcst_recv_buf, '\0', sizeof(brdcst_recv_buf));

			
	}//infinte while
	
	printf("\n\tBroadcast thread done with thread id = %ld\n\n", pthread_self());

	//removing this client from active client list
	ret_val = -1;
	ret_val = remove_from_active_client_list(list, connfd);
	if (SUCCESS == ret_val)
	{
		printf("\n\tSuccessfully removed from active client list !!\n\n");		
	}
	else
	{
		log_server_report(ERROR, "ERROR : Error Removing active client", __FILE__, __LINE__);
		printf("\n\tError removing from active client list !!\n\n");	
	}

	log_server_report(NORMAL, "THREAD EXIT: broadcast_handler", __FILE__, __LINE__);

	close(connfd);
	pthread_exit(NULL);
	
}
