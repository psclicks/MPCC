
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

#include <client_util.h>
			
/******************************************************************************
 *	FUNCTION NAME	: main
 *
 *	DESCRIPTION	: function calls get_login_details for testing 
 *
 *	RETURNS 	: SUCCESS or FAILURE
 *
*******************************************************************************/


int main()
{
	char buf[50] ="\0";
	int res = get_login_details(buf);
	if (res)
	{
		printf("\nGet login details runs successfully\n\n");
	}
	else
	{
		printf("\nGet login details function failed\n\n");
	}

	return 0;
}	