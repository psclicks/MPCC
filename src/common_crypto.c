/*********************************************************************************
*
*  FILE NAME   : common_crypto.c
*
*  DESCRIPTION : contails defination for cryptography functions
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
**********************************************************************************/

/*********************************************************************************
				STANDARD HEADER FILES
**********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*********************************************************************************
					LOCAL MACROS
**********************************************************************************/

//key used to encrypt/dencrypt msg
#define EKEY 0xFACA

#define SUCCESS 1;

/**********************************************************************************
 *
 *   FUNCTION NAME : encrypt
 *
 *   DESCRIPTION   : This function encrypts the data pointed by buf ptr.
 *
 *   RETURNS 	     : SUCCESS on successful execution.
 *
***********************************************************************************/

int encrypt(char *buf)
{	
	int i = 0;	
	for (i = 0; i < (int)strlen(buf); i++)
	{ 
		buf[i] = buf[i] + (char)EKEY;
	}
	return SUCCESS;
}


/*********************************************************************************
 *
 *   FUNCTION NAME : decrypt
 *
 *   DESCRIPTION   : This function decrypt the data pointed by buf ptr.
 *
 *   RETURNS	     : SUCCESS on successful execution.
 *
**********************************************************************************/

int decrypt(char *buf)
{
	int i = 0;
	for (i = 0; i < (int)strlen(buf); i++)						
	{
		buf[i] = buf[i] - (char)EKEY;
	}
	return SUCCESS;
}
