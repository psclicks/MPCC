/******************************************************************************
*
*  FILE NAME   : stub_driver.c
*
*  DESCRIPTION : it includes stub and driver functions. 
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

#include <server_util.h>
			
/******************************************************************************
 *	FUNCTION NAME	: stub_authenticate
 *
 *	DESCRIPTION	: function returns buffer storing data to test existing
				client processing function
 *
 *	RETURNS 	: returns a character buffer.
 *
*******************************************************************************/


char *stub_authenticate()
{
	char *buf = "abc:123\0";

	return buf;
}

