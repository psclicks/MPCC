/******************************************************************************
*
*  FILE NAME   : add_to_reg_user_file.c
*
*  DESCRIPTION : it include funtion to adds the new user details to reg_user_file
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
********************************************************************************/

/******************************************************************************
 *	ALL NECESSARY COMMON HEADERS, MACROS AND FUNCTIONS FOR CLIENT PROGRAM
*******************************************************************************/

#include <server_util.h>			

/******************************************************************************
 * FUNCTION NAME : add_to_reg_user_file
 *
 * DESCRIPTION   : This funtion adds the new user details to reg_user_file 
 * 	
 * RETURNS	   : retuns SUCCESS or FAILURE
 
*******************************************************************************/

int add_to_reg_user_file(
			char *recv_buf)	/* for new userid & password */
{
	log_server_report(NORMAL, "Entering : add_to_reg_user_file function", __FILE__, __LINE__);		//writing to the output log file

	FILE *append_fp = NULL;
	int ret_val = -1;

	append_fp = fopen(PATH, "a");										//opening the reg_user file to append the new user login and pass			

	if (!append_fp)												//validation then proceeding
	{
		log_server_report(ERROR, "ERROR : in add_to_reg_user_file", __FILE__, __LINE__);		//writing the error message to log file
		printf("\n\tERROR : While opening registered user file !!\n\n");
		
		return FAILURE;
	}
	else
	{
		ret_val = fprintf(append_fp, "%s\n", recv_buf);							//append formated contents from buf to the file
		if (ret_val <= 0)
		{
			printf("\n\tError : in fprintf !!\n\n");							//printing the error message
			
			fclose(append_fp);										//closing the file 

			log_server_report(ERROR, "ERROR : fprintf Error", __FILE__, __LINE__);

			return FAILURE;
		}
	 
		fclose(append_fp);											//closing the file	
		log_server_report(NORMAL, "Exiting : add_to_reg_user_file function", __FILE__, __LINE__);	//writing to the output log file				

		return SUCCESS;											//returning SUCCESS status 
	}
}