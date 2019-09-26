/******************************************************************************
*
*  FILE NAME    : client_util.h
*
*  DESCRIPTION  : This file contains common Macros and declaration of following
*		    functions :
*		    1. send_to_server 
*		    2. recv_from_server 
*		    3. get_login_details 		    
*		    4. new_user_working 
*		    5. existing_user_working 			  		    
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
*******************************************************************************/

#ifndef __CLIENT_UTIL_H_
#define __CLIENT_UTIL_H_

/***************************************************************************
			COMMON	STANDARD HEADER FILES
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <signal.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/time.h>

#include <pthread.h>					//for using pthread API

/******************************************************************************
 *				COMMON MACROS
*******************************************************************************/

#define SUCCESS 1
#define FAILURE 0
#define BUFFER_SIZE 1024

#define MAX_SIZE 100

//to logging the data in a file
#define NORMAL 1
#define ERROR 0


//to be used in switch case
#define NEW_USER 1
#define EXISTING_USER 2
#define EXIT 3

//to logging the data in a file
#define NORMAL 1
#define ERROR 0

//to seperate userid and password
#define DELIMITER ":"

//to logout client
#define LOGOUT "byebye"

//macro for log report path 
#define LOGPATH "..//log//client_log"

//macro to remove "\n" i.e. new line char from input
#define TRIM_LINE(x) (x[strlen(x) - 1] = '\0')

/******************************************************************************
 *		ALL FUNCTION DEFINITION FOR CLIENT PROGRAM
*******************************************************************************/

//This function sends login details to Server
int send_to_server(int socket_fd, char *send_buf);

//This function receive the message send by Server
int recv_from_server(int socket_fd, char *recv_buf);

//This function is getting the login id and password from Client
int get_login_details(char *send_buf);

//function to process new client
int new_user_processing(int socket_fd, char *send_buf, char *recv_buf);

//function to process exixting client
int existing_user_processing(int socket_fd, char *send_buf, char *recv_buf);

//function to handle recv broadcast threads
void *brdcst_recv_handler(void *sockfd);

//function to handle send broadcast threads
void *brdcst_send_handler(void *sockfd);

//function to trace everything which is going in the client side in a log file
void log_client_report(int type, char *msg, char *file, int line);

#endif
