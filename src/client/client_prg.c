/******************************************************************************
*
*  FILE NAME    : client_prg.c
*
*  DESCRIPTION  : This file demonstrate implemention of client which is doing 
*		    following function :
*		    1. Creating the socket
*		    2. Establishing connection with Server
*		    3. Selection options
*			(a). New User Registration
*			(b). Existing User Login
*
*		    4. (a). New User Registration : 
*			1. Enter the unique login id
*			2. Enter password
*			3. Sending details to Server
*			4. Wait for server authentication
*			5. If get the message "Registered Successfully" from 
*				Server then calls the Existing User Login page
*
*		    5. (b). Existing User Login :
*			1. Enter Existing login id
*			2. Enter password
*			3. Send details to Server
*			4. Receive message from Server
*				(a). "incorrect details" : details that entered by 
*					client is incorrect . Please re-enter correct 
*					details (optional)
*				(b). "Successfully login to the Conference Chat Room" 
*					Send message to broadcast to other Clients 
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1 	Multi Party Conference Chat		Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
*******************************************************************************/


/******************************************************************************
 *	ALL NECESSARY COMMON HEADERS, MACROS AND FUNCTIONS FOR CLIENT PROGRAM
*******************************************************************************/

#include <client_util.h>

/******************************************************************************
 *				LOCAL MACROS
*******************************************************************************/

#define MIN_ARGS 3

typedef struct sockaddr SA;

/******************************************************************************
 *	FUNCTION NAME	: main
 *
 *	DESCRIPTION	: This is main function for calling others functions
 * 	
 *	RETURNS	: Returns SUCCESS as exit status
 *
*******************************************************************************/

int main(int argc,		/* number of runtime arguments */
 	  char *argv[])	/* pointer to the array that stores the runtime arguments */
{

	/************* Validating Runtime Arguments ****************/
	
	if (argc < MIN_ARGS)
	{
		printf("\n\tRuntine Arguments Expected: <Server IP Address> <Server Port No> !!\n\n");		//printing the error message
		exit(EXIT_FAILURE);												//exiting the main function
	}
	if ((atoi(argv[2]) < 1024) || (atoi(argv[2]) > 65535))
	{
		perror("\n\tInvalid port no entered \n\n");
		exit (EXIT_FAILURE);
	}

	(void)system("clear");       											//clearing console

	/************* Initialization ****************/

	int socket_fd = -1;
	int status = 0;
	int option = 0;

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));									//initialising the structure with NULL

	char send_buf[BUFFER_SIZE] = {'\0'};
	char recv_buf[BUFFER_SIZE] = {'\0'};

	/*************** Creating Client Socket ************/

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)								//creating and validating the socket_fd
	{
		
		perror("\n\tSOCKET ERROR ");										//printing the error message
		exit(EXIT_FAILURE);												//exiting the main function
		
	}
	
	/********* Initializing the fields of server_addr structure *********/

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));

	if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0)
	{
		printf("\n\tERROR : Invalid Address or Address not supported \n\n");					//printing the error message
		close(socket_fd);
		exit(EXIT_FAILURE);												//exiting the main function
	}

	/******** Establishing Connection with Server ************/

	if (connect(socket_fd, (SA *)&server_addr, sizeof(server_addr)) < 0)						//validating the connect function
	{	
		perror("\n\tCONNECT ERROR ");										//printing the error message
		close(socket_fd);												//closing the socket_fd
		exit(EXIT_FAILURE);												//exiting the main function
	}

	(void)system("clear");       												//clearing console

	printf("\n\tClient has Connected to the Server.............\n\n");

	/****************** Choose Options ***********************/

	printf("\n\t--------- Welcome Please Choose one Option -------\n\n");
	printf("\n\t 1. NEW USER REGISTRATION \n");
	printf("\n\t 2. EXISTING USER LOGIN \n");
	printf("\n\t 3. EXIT \n\n");

	printf("\n\tEnter your choice = ");
	scanf("%d", &option);											//input the option from user

	sprintf(send_buf, "%d", option);										//converting integer to string
	status = send_to_server(socket_fd, send_buf);								//sending option to Server

	if (status == SUCCESS)											//Validating the send_to_server funtion
	{
		printf("\n\tOption send to Server\n");
	}
	else
	{
		printf("\n\tError in sending option to Server\n");
		close(socket_fd);											//closing socket_fd
		
		exit(EXIT_FAILURE);											//exiting the main
	}

	memset(send_buf, '\0', strlen(send_buf));									//flushing send_buf before reuse

	switch(option)
	{
		/************ Calling new_user_processing function and storing its return status ***********/
		case NEW_USER :

				log_client_report(NORMAL, "Entering : NEW_USER OPTION", __FILE__, __LINE__);					//writing in output log file
				status = new_user_processing(socket_fd, send_buf, recv_buf);				//calling new_user_processing function to handle new registration case		
		
				if (status == FAILURE)									//Validating the new_user_processing function
				{
					log_client_report(ERROR, "ERROR : new_user", __FILE__, __LINE__);

					printf("\n\tError in new_user_processing function of Client \n\n");		//printing the error message
					
					close(socket_fd);									//closing the socket_fd
					exit(EXIT_FAILURE);									//exiting the main function
				} 
				break;
		
		/************ Calling existing_user_processing function and storing its return status ***********/
		case EXISTING_USER :
					log_client_report(NORMAL, "Entering : EXISTING_USER_OPTION", __FILE__, __LINE__);
					status = existing_user_processing(socket_fd, send_buf, recv_buf);			//calling existing_user_processing function to handle login case
 
					if (status == FAILURE)									//Checking the status of existing_user_processing function
					{
						log_client_report(ERROR, "ERROR : Existing_user_processing", __FILE__, __LINE__);
						printf("\n\tError in existing_user_processing function of Client \n\n");	//printing the error message
			
						close(socket_fd);									//closing the socket_fd
						exit(EXIT_FAILURE);									//exiting the main function
					}
					break;
		
		case EXIT :
				printf("\n\tClient have Exited !!\n\n");
				close(socket_fd);											//closing the socket_fd
				exit(EXIT_SUCCESS);
				break;

		default : 
				log_client_report(ERROR, "ERROR : Invalid choice", __FILE__, __LINE__);							//writing the error message in output log file
				printf("\n\tInvalid Choice received !!\n\n");
				break;
																	//exiting the main function
	}

	close(socket_fd);														//closing the socket_fd

	return SUCCESS;														//Successfully returning from main function
}






		

