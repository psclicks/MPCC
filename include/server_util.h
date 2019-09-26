/***************************************************************************
*
*  FILE NAME   : server_util.h
*
*  DESCRIPTION : header file for utility functions used by concurrent server  
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
***************************************************************************/

#ifndef __SERVER_UTIL_H_
#define __SERVER_UTIL_H_

/***************************************************************************
			COMMON	STANDARD HEADER FILES
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/time.h>

#include <gmodule.h>					//glib header file for GSList
#include <pthread.h>					//for using pthread API


/***************************************************************************
				GLOBAL VARIBALES
****************************************************************************/

//global mutex variable for sync while adding userid to reg user file
pthread_mutex_t thread_add_to_file_mutex;

//global mutex variable for sync while adding active client to the list
pthread_mutex_t thread_add_to_list_mutex;


/***************************************************************************
					MACROS
****************************************************************************/

//for functions returns
#define SUCCESS 1
#define FAILURE 0

//for n/w buf sizes
#define MAX_SIZE 1024

//to logging the data in a file
#define NORMAL 1
#define ERROR 0

//for max no of clients 
#define MAX_CLIENTS 50

//for max lenght of userid or pass 
#define MAX_LEN 100

//macro for path
#define PATH "..//dat//registered_users"

//macro for log report path 
#define LOGPATH "..//log//server_log"

//to seperate userid and password
#define DELIMITER ":"

//macro to remove "\n" i.e. new line char from input
#define TRIM_LINE(x) (x[strlen(x) - 1] = '\0')

//macro for free the heap mem
#define FREE(x) 	  	\
	if (x)			\
	{			\
		free(x);	\
		x = NULL;	\
	}			\

//to be used in switch case
#define NEW_USER 1
#define EXISTING_USER 2
#define EXIT 3

//macro fro thread cleanup
#define THREAD_CLEANUP\
			printf("\n\tClient thread with thread id = %ld is done....\n\tnow closing client conection...bye\n\n", pthread_self());\
			\
			close(connfd);\
			\
			pthread_exit(NULL);\



/***************************************************************************
					STRUCTURE
****************************************************************************/
//structure to store active clients details
typedef struct active_client_data_t
{
	int connfd;		//to store connfd of client
	char *userid;		//to store auth_userid addr
	
}ACTIVE_CLIENT;

//structure to store data to be passed to thread handler
typedef struct thread_data_t
{
	int clientfd;					//to store new clientfd
	GSList **list;				//to pass gslist ptr
	pthread_mutex_t *file_mutex;		//to store file mutex addr
	pthread_mutex_t *list_mutex;		//to store list mutex addr
	
}TH_DATA;

//structure to store data to be passed to broadcast thread handler
typedef struct broadcast_thread_data_t
{
	int clientfd;					//to store current clientfd
	GSList **list;				//to pass gslist ptr
	
}BRD_TH_DATA;

/***************************************************************************
				FUNCTIONS PROTOTYPES
****************************************************************************/

//function to send data to the connected client
int send_to_client(int connfd, char *buf);

//function to recv data from the connected client
int recv_from_client(int connfd, char *buf);

//function to authenticate client using userid & pass
char *client_authentication(char *buf);

//function to handle client threads
void *client_handler(void *th_data);

//function to handle broadcast threads
void *broadcast_handler(void *brd_th_data);

//function to process exixting client
int existing_user_processing(pthread_mutex_t *list_mutex, GSList **list, int connfd, char *recv_buf, char *send_buf);

//function to process new client
int new_user_processing(pthread_mutex_t *file_mutex, GSList **list, int connfd, char *recv_buf, char *send_buf);

//function to check wheather user already present in the reg user 
int is_user_exist(char *buf);

//function to append new client details to user file
int add_to_reg_user_file(char *recv_buf);

//function adds the authenticated client to active_client_list
int add_to_active_client_list(GSList **list, int connfd, char *auth_userid);

//function remove client from active_client_list
int remove_from_active_client_list(GSList **list, int connfd);

//callback function to free each node data of gslist
void free_func(gpointer data);

//callback function to display each node data of gslist
void display_list(gpointer data, gpointer user_data);

//callback function to be find client for each list node
gint find_client(gconstpointer data1, gconstpointer data2);

//function to trace everything which is going in the server side in a log file
void log_server_report(int type, char *msg, char *file, int line);

//the stub dummy code for authentication function
#define STUB_AUTHENTICATE
char *stub_authenticate();

#endif

