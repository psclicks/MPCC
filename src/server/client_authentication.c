/*********************************************************************************
*
*  FILE NAME   : client_authentication.c
*
*  DESCRIPTION : it include all authentication functions required by the server.
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
**********************************************************************************/

#include <server_util.h>			//contails all macros and header files

/*********************************************************************************
 * FUNCTION NAME	: client_authentication
 *
 * DESCRIPTION	: function to authenticate client using userid & pass 
 *  	
 * RETURNS	: return userid(heap address) of authenticated client or NULL on failure 

**********************************************************************************/

char *client_authentication(
				char *buf)		/* for received usidid:pass */
{	
	log_server_report(NORMAL, "Entering : client_authentication", __FILE__, __LINE__);
	FILE *read_fp = NULL;

	//making read streams
	read_fp = fopen(PATH, "r");

	//validation then proceeding
	if (!read_fp)
	{
		log_server_report(ERROR, "ERROR : CLIENT_AUTHENTICATION", __FILE__, __LINE__);
		printf("\n\tERROR : While opening registered user file !!\n\n");
		
		return NULL;
	}
	else
	{	char *auth_userid = NULL;
		char *recv_userid = NULL;
		char *recv_pass = NULL;
		char local_buf[MAX_SIZE] = {'\0'};
		char line_buf[MAX_LEN] = {'\0'};
		char *userid = NULL;
		char *pass = NULL;
		
		//copying data to local buf before tokenizing with validation
		if ((strlen(buf) + 1) <= sizeof(local_buf))
		{
			strcpy(local_buf, buf);
		}
		else
		{			
			log_server_report(ERROR, "ERROR : new_user_processing", __FILE__, __LINE__);
			printf("\n\tLocal Buffer Size is too small !!\n\n");

			//closing the file streams
   			fclose(read_fp);
		
			return NULL;
		}
		
		//getting received credentials
		recv_userid = strtok(local_buf, DELIMITER);
		recv_pass = strtok(NULL, DELIMITER);
		
		//Read contents from file and validating with recv credentials 
		while (NULL != fgets(line_buf, MAX_LEN, read_fp))
		{
	
			//removing new line char 
			TRIM_LINE(line_buf);

			//getting stored credentials
			userid = strtok(line_buf, DELIMITER);
			pass = strtok(NULL, DELIMITER);

			//matching credentials
			if (!strcmp(recv_userid, userid))
			{
				if (!strcmp(recv_pass, pass))
				{
					auth_userid = (char *)calloc((strlen(userid)+1), sizeof(char));

					strcpy(auth_userid, userid);

  					fclose(read_fp);

					return auth_userid;
						
				}
				else
				{
					log_server_report(ERROR, "ERROR : Client Authentication", __FILE__, __LINE__);
					log_server_report(ERROR, "ERROR : CLIENT_AUTHENTICATION", __FILE__, __LINE__);

					printf("\n\tUserid found but PASSWORD is incorrect !!\n\n");

					fclose(read_fp);

					return NULL;					
				}

				//filling null before taking new line data from file
				bzero(&userid, sizeof(userid));		//filling with 0 valued bytes
				bzero(&pass, sizeof(pass));			//filling with 0 valued bytes

			}
		}
		
		//closing the file streams
   		fclose(read_fp);
		log_server_report(NORMAL, "Exiting : client_authentication", __FILE__, __LINE__);	
		return NULL;
	
	}//else end
}