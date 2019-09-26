/******************************************************************************
*
*  FILE NAME   : get_login_details.c
*
*  DESCRIPTION : it include functions to take userid and password from user
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
 *	FUNCTION NAME	: get_login_details
 *
 *	DESCRIPTION	: function to get the login id and password from Client 
 *			  and stored in send_buf
 *
 *	RETURNS 	: SUCCESS or FAILURE
 *
*******************************************************************************/

int get_login_details(
			char *send_buf)		/* for storing the login id and 
						   	   password in send_buf */
{
	log_client_report(NORMAL, "Entering : Get_login_details", __FILE__, __LINE__);			//Writing to the output log file
	
	char id[MAX_SIZE] = {'\0'};
	char passwd[MAX_SIZE] = {'\0'};

	printf ("\n\tENTER UNIQUE LOGIN ID : ");
	scanf ("%s", id);												//getting the login id from Client
		
	strcat(send_buf, id);											//concatinating the login id to send_buf
	strcat(send_buf, ":");											//concatinating the DELIMITER ":" to send_buf

	printf ("\n\tENTER PASSWORD : ");
	scanf ("%s", passwd);											//getting the password from Client

	strcat(send_buf, passwd);											//concatinating the password to send_buf

	log_client_report(NORMAL, "Exiting : Get_login_details", __FILE__, __LINE__);

	return SUCCESS;												//returning SUCCESS status to calling function
}
	