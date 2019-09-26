/***************************************************************************
*
*  FILE NAME   : common_crypto.h
*
*  DESCRIPTION : header file for cryptography functions declaration  
*
*  DATE	NAME		REFERENCE				REASON
*  23/04/18	GR_TH5_C_1	Multi Party Conference Chat	  	Nalanda Project
*
*  Copyright 2018, Aricent Tech. (Holdings) Ltd.
*
***************************************************************************/

#ifndef __COMMON_CRYPTO_H_
#define __COMMON_CRYPTO_H_


/***************************************************************************
				FUNCTIONS PROTOTYPES
****************************************************************************/

//This function encrypt the data pointed by buf ptr.
int encrypt(char *buf);

//This function decrypt the data pointed by buf ptr.
int decrypt(char *buf);

#endif