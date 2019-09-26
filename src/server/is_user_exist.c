/*********************************************************************************
*
*  FILE NAME   : is_user_exist.c
*
*  DESCRIPTION : it include funtion to check wheather user already or not
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
**********************************************************************************/

#include <server_util.h>			//contails all macros and header files

/*********************************************************************************
 * FUNCTION NAME : is_user_exist
 *
 * DESCRIPTION   : funtion to check wheather user already present in the reg user 
 *  	
 * RETURNS : return SUCCESS if user exists else FAILURE if user not exists in file

**********************************************************************************/

int is_user_exist(
			char *buf)		/* for received usidid */
{	
	FILE *read_fp = NULL;

	log_server_report(NORMAL, "Entering : is_user_exist", __FILE__, __LINE__);

	//making read streams
	read_fp = fopen(PATH, "r");

	//validation then proceeding
	if (!read_fp)
	{
		log_server_report(ERROR, "ERROR : is_user_exist", __FILE__, __LINE__);

		printf("\n\tERROR : While opening registered user file !!\n\n");
		
		return -1;
	}
	else
	{	char *recv_userid = NULL;
		char local_buf[MAX_SIZE] = {'\0'};
		char line_buf[MAX_LEN] = {'\0'};
		char *userid = NULL;
		
		//copying data to local buf before tokenizing with validation
		if ((strlen(buf) + 1) <= sizeof(local_buf))
		{
			strcpy(local_buf, buf);
		}
		else
		{

			log_server_report(ERROR, "ERROR : is_user_exist", __FILE__, __LINE__);

			printf("\n\tLocal Buffer Size is too small !!\n\n");

			//closing the file streams
   			fclose(read_fp);
		
			return -1;
		}
		
		//getting received credentials
		recv_userid = strtok(local_buf, DELIMITER);
		
		//Read contents from file and validating with recv credentials 
		while (NULL != fgets(line_buf, MAX_LEN, read_fp))
		{
	
			//removing new line char 
			TRIM_LINE(line_buf);

			//getting stored credentials
			userid = strtok(line_buf, DELIMITER);

			//matching userids
			if (!strcmp(recv_userid, userid))
			{
				return SUCCESS;
			}

			//filling null before taking new line data from file
			bzero(&line_buf, sizeof(line_buf));		//filling with 0 valued bytes
			bzero(&userid, sizeof(userid));			//filling with 0 valued bytes
		}
		
		//closing the file streams
   		fclose(read_fp);
		
		//userid not fount in file
		return FAILURE;

		log_server_report(NORMAL, "Exiting : is_user_exist", __FILE__, __LINE__);
	
	}//else end
}