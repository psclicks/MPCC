/******************************************************************************
*
*  FILE NAME   : server_prg.c
*
*  DESCRIPTION : This file demonstrate implemention of concurrent server which 			 
*		   is doing following function :
*
*		   1. Creating a listening socket to listen for clients.
*		   2. Binding this listening socket to ip & port taken at runtime.
*		   3. Establishing new connection with clients and assigning it
*		      to the new thread using client_handler function.
*		   4. Maintanence & closing of connected clients.
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
*******************************************************************************/ 

#include <server_util.h>			//all neccessary common macros & fun


/***************************************************************************
				LOCAL MACROS
****************************************************************************/
//for runtime args
#define MIN_ARGS 3

//used in listen call as backlog val
#define WAIT_QUEUE_LEN 5


/***************************************************************************
 * FUNCTION NAME : main
 *
 * DESCRIPTION   : this is main function for calling others funs
 * 	
 * RETURNS	   : Returns SUCCESS as exit status

***************************************************************************/

int main(
		int argc,		/* no of runtime args */ 
		char **argv)		/* ptr arrray to store runtime args */
{
	/*
	* valadating runtime args
	*/
	if (argc < MIN_ARGS)
	{
		printf("\n\tRuntine Args Expected : <Start ip of Server> <Start port of Server> !!\n\n");
		exit (EXIT_FAILURE);
	}
	if ((atoi(argv[2]) < 1024) || (atoi(argv[2]) > 65535))
	{
		perror("\n\tInvalid port no entered \n\n");
		exit (EXIT_FAILURE);
	}

	(void)system("clear");       	//clearing console
	
	/*
	* initialization
	*/
	int listenfd = -1;
	int connfd = -1;
	int ret_val = -1;
	pthread_t thread_id;

	GSList *active_client_list = NULL;
	
	struct sockaddr_in server_addr, client_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	memset(&client_addr, 0, sizeof(client_addr));

	socklen_t client_addr_len = sizeof(client_addr);
	
	/*
	* making listening socket
	*/
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == listenfd)
	{
		perror("\n\tSOCKET ERROR ");
		return FAILURE;
	}

	/*
	* filling server details
	*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));	
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	/*
	* binding ip & port to listening socket
	*/
	ret_val = bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (-1 == ret_val)
	{
		perror("\n\tBIND ERROR ");
		close(listenfd);
		return FAILURE;
	}
	
	/*
	* putting listenfd socket in listen state
	*/ 
	ret_val = listen(listenfd, WAIT_QUEUE_LEN);
	if (-1 == ret_val)
	{
		perror("\n\tLISTEN ERROR ");
		close(listenfd);
		return FAILURE;
	}

	/*
	* thread_add_to_file mutex initialization  
	*/
	ret_val = -1;
	ret_val = pthread_mutex_init(&thread_add_to_file_mutex, NULL);
	if (ret_val)
	{
		perror("\n\tthread_add_to_file_mutex initialization failed ");
		close(listenfd);
		return FAILURE;
	}
	
	/*
	* thread_add_to_list mutex initialization  
	*/
	ret_val = -1;
	ret_val = pthread_mutex_init(&thread_add_to_list_mutex, NULL);
	if (ret_val)
	{
		perror("\n\tthread_add_to_list_mutex initialization failed ");
		close(listenfd);
		return FAILURE;
	}

	/*
	* waiting for clients in listening mode
	*/ 
	printf("\n\t------ SERVER RUNNING & WAITING FOR CLIENTS -----\n\n\n");
	log_server_report(NORMAL," SUCCESS IN : Starting SERVER", __FILE__, __LINE__);
	for ( ; ; )
	{	
		//calling accept for clients	
		connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_addr_len);
		if (-1 == connfd)
		{
			perror("\n\tCONNECTION ERROR ");
			continue;
		}


		//connected client info
		printf("\n\tConnected to client's ip : %s with client's port : %d\n\n", 
			inet_ntoa(client_addr.sin_addr), 
			(int)client_addr.sin_port);

		//creating obj of new client
		TH_DATA th_data;
		memset(&th_data, 0 ,sizeof(th_data));

		th_data.clientfd = connfd;
		th_data.list = &active_client_list;
		th_data.file_mutex = &thread_add_to_file_mutex;
		th_data.list_mutex = &thread_add_to_list_mutex;
	
		/*
		* now creating new threads to handle clients  
		*/		
		ret_val = pthread_create(&thread_id, NULL, client_handler, (void*)&th_data);
		if (ret_val)
		{
			perror("\n\tTHREAD ERROR ");
			continue;
		}		
			
	}//infinte for ends 


	//closing servers's listening socket
	close(listenfd);

	//freeing complete active clients list
	g_slist_free_full(active_client_list, (GDestroyNotify) free_func);	//free_func to be called for each gslist node

	/*
	* thread_add_to_file mutex destroying 
	*/
	ret_val = -1;
	ret_val = pthread_mutex_destroy(&thread_add_to_file_mutex);
	if (ret_val)
	{
		perror("\n\tthread_add_to_file_mutex destroying failed ");
	}

	/*
	* thread_add_to_list mutex destroying 
	*/
	ret_val = -1;
	ret_val = pthread_mutex_destroy(&thread_add_to_list_mutex);
	if (ret_val)
	{
		perror("\n\tthread_add_to_list_mutex destroying failed ");
	}

	return SUCCESS;
	
} 



