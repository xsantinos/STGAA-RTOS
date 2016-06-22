/** @file Modem.c
 *  @brief Transmits the records stored in the SD memory to the remote server by GPRS.
 *
 *  Modem responsible for\n
 *  -.\n
 *  -.\n
 * @version		1.0
 * @date		29/03/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#include "Modem.h"
#include "GL865.h"


/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
MOD_ERROR_T error;

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief
 * @param
 * @return
 */
void MOD_TicksInput(void){
	GL865_Timerproc();

//	#if defined (__DEBUG_ON)
//    	printf("->buf: ");
//    	uint8_t i = 0;
//    	for(i=0;i<BUF_LENGTH;i++)
//    		{printf("%c",buf[i]);}
// 	   printf("\r\n");
//	#endif

}

/**
 * @brief
 * @param
 * @return
 */
void MOD_Open(void){

	if(GL865_Init()==SUCCESS){
	#if defined (__DEBUG_ON)
		printf("Modem Initialized: OK...\r\n");
	#endif
	}
	else{
	#if defined (__DEBUG_ON)
		printf("Modem Initialized: OK...\r\n");
	#endif
		error=MODEM_INIT_FAIL;
	}
}

/**
 * @brief
 * @param
 * @return
 */
void MOD_GetSignal(char *signal){
	*signal=GL865_GetSignal();
}

/**
 * @brief
 * @param
 * @return
 */
void MOD_GetVersion(char *version){
	GL865_GetVersion();
}

/**
 * @brief
 * @param
 * @return
 */
void MOD_RequestHTTP(char* domain){

}

/**
 * @brief
 * @param
 * @return
 */
void MOD_RequestFTP(char* domain){

}

/**
 * @brief
 * @param
 * @return
 */
void MOD_Login(char* credentials){

}

/**
 * @brief
 * @param
 * @return
 */
void MOD_Close(void){

}

