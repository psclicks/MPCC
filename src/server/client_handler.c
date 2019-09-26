/*********************************************************************************
*
*  FILE NAME   : client_handler.c
*
*  DESCRIPTION : it include start routine function for client threads handling
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
**********************************************************************************/
#ifndef S_SPLINT_S

#include <server_util.h>			//contails all macros and header files

#endif

/*********************************************************************************
 * FUNCTION NAME : client_handler
 *
 * DESCRIPTION   : this is start routine function for threads
 * 	
 * RETURNS	   : retuns nothing but exit thread at end
 
**********************************************************************************/

void *client_handler(
		void *th_data)	/* TH_DATA obj is passed as the arg */
{
	pthread_detach(pthread_self());	
	/*
	* NOTES: The  pthread_detach() function marks the thread identified by thread as detached. 
	* When a detached thread terminates, its resources are automatically released back to the
       * system without the need for another thread to join with the terminated thread.
	*/

	log_server_report(NORMAL, "THREAD START: client handlier", __FILE__, __LINE__);

	printf("\n\tNew Client thread started with thread id = %ld\n\n", pthread_self());

	TH_DATA *thread_data = (TH_DATA*)th_data;
	int connfd = thread_data->clientfd;
	GSList **list = thread_data->list;

	int ret_val = -1;
	int choice = 0;
	pthread_t thread_id;
	
	char send_buf[MAX_SIZE] = {'\0'};
	char recv_buf[MAX_SIZE] = {'\0'};

	//receiving choice from client
	ret_val = recv_from_client(connfd, recv_buf);
	if (SUCCESS == ret_val)
	{
		choice = atoi(recv_buf);

		//flushing buf to be reuse
		memset(recv_buf, '\0', strlen(recv_buf));
	}
	else
	{
		log_server_report(ERROR, "ERROR : NEW_USER OPTION", __FILE__, __LINE__);
		printf("\n\tNo data (choice) received from client !!\n\n");

		//macro for cleanup
		THREAD_CLEANUP;
	}

	switch(choice)
	{
		case NEW_USER :  
					log_server_report(NORMAL, "Entering : NEW_USER", __FILE__, __LINE__);
					ret_val = -1;
					ret_val = new_user_processing(thread_data->file_mutex, list, connfd, recv_buf, send_buf);
					if (SUCCESS == ret_val)
					{
						//new user successfully registerd now asking to login again 

						printf("\n\tWaiting for relogin !!\n\n");

						ret_val = -1;
						ret_val = existing_user_processing(thread_data->list_mutex, list, connfd, recv_buf, send_buf);
						if (SUCCESS == ret_val)
						{
							printf("\n\tAuthentication successful....\n\tNow creating broadcast thread\n\n");
						
							//creating obj of new client
							BRD_TH_DATA brd_th_data;
							memset(&brd_th_data, 0 ,sizeof(brd_th_data));

							brd_th_data.clientfd = connfd;
							brd_th_data.list = list;
	
							/*
							* now creating new broadcast thread 
							*/	
							ret_val = -1;	
							ret_val = pthread_create(&thread_id, NULL, broadcast_handler, (void*)&brd_th_data);
							if (ret_val)
							{
								printf("\n\tUnable to create the broadcast thread \n");
								perror("Broadcast Thread ");

								//macro for cleanup
								THREAD_CLEANUP;				
							}
			
							/*
							* now waiting for new broadcast thread to complete 
							*/
							ret_val = -1;
							ret_val = pthread_join(thread_id, NULL); 
							if (-1 == ret_val)
							{
								printf("\n\tUnable to join the broadcast thread \n");
								perror("Broadcast Thread ");

								//macro for cleanup
								THREAD_CLEANUP;					
							}

						}
						else
						{
							//cleanup on FAILURE return by existing_user_processing
			
							//macro for cleanup
							THREAD_CLEANUP;
						}
					}
					else
					{
						//cleanup on FAILURE return by new_user_processing
			
						//macro for cleanup
						THREAD_CLEANUP;
					}

		
					break;

		case EXISTING_USER : 
					log_server_report(NORMAL, "Entering : EXISTING OPTION", __FILE__, __LINE__);
					ret_val = -1;
					ret_val = existing_user_processing(thread_data->list_mutex, list, connfd, recv_buf, send_buf);
					if (SUCCESS == ret_val)
					{
						printf("\n\tAuthentication successful....\n\tNow creating broadcast thread\n\n");
						
						//creating obj of new client
						BRD_TH_DATA brd_th_data;
						memset(&brd_th_data, 0 ,sizeof(brd_th_data));

						brd_th_data.clientfd = connfd;
						brd_th_data.list = list;
	
						/*
						* now creating new broadcast thread 
						*/	
						ret_val = -1;	
						ret_val = pthread_create(&thread_id, NULL, broadcast_handler, (void*)&brd_th_data);
						if (ret_val)
						{
							printf("\n\tUnable to create the broadcast thread \n");
							perror("Broadcast Thread ");

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

							//macro for cleanup
							THREAD_CLEANUP;				
						}
			
						/*
						* now waiting for new broadcast thread to complete 
						*/
						ret_val = -1;
						ret_val = pthread_join(thread_id, NULL); 
						if (-1 == ret_val)
						{
							printf("\n\tUnable to join the broadcast thread \n");
							perror("Broadcast Thread ");

							//removing this client from active client list
							ret_val = -1;
							ret_val = remove_from_active_client_list(list, connfd);
							if (SUCCESS == ret_val)
							{
								printf("\n\tSuccessfully removed from active client list !!\n\n");		
							}
							else
							{
								log_server_report(ERROR, "ERROR : Error Removing Active Client", __FILE__, __LINE__);
								printf("\n\tError removing from active client list !!\n\n");	
							}

							//macro for cleanup
							THREAD_CLEANUP;					
						}

					}
					else
					{
						//cleanup on FAILURE return by new_user_processing
			
						//macro for cleanup
						THREAD_CLEANUP;
					}
					
					break;

		case EXIT :
				printf("\n\tClient have Exited !!\n\n");
	
				break;

		default : 
				printf("\n\tInvalid Choice received from client !!\n\n");
				break;
	}

	log_server_report(NORMAL, "exiting client handler", __FILE__, __LINE__);

	//macro for cleanup
	THREAD_CLEANUP;
}
