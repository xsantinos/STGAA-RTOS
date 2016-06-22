
/** @file Transceiver.c
 *  @brief Transmits the records stored in the SD memory to the remote server by GPRS.
 *
 *  Transceiveris responsible for\n
 *  -.\n
 *  -.\n
 * @version		1.0
 * @date		08/04/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#include "Common.h" /*RTOS types and structures*/
#include "Transceiver.h"
#include "Modem.h"
#include "GPRS.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

char signal;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
/**
 * @brief 		Refreshing thread
 * @param   	pvParameters is void pointer.
 * @return 		None
 */
static void vModemTickTask(void *pvParameters){

	while(1){
		MOD_TicksInput();
		vTaskDelay(10 / portTICK_RATE_MS);
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/
char TRX_GetSignal(void){
	return signal;
}



void TRX_InitDriver(void){
	MOD_Open();
}


/**
 * @brief 		Acquiring thread
 * @param   	pvParameters is void pointer.
 * @return 		None
 */
void vTransmittingTask(void *pvParameters) {

	if(xTaskCreate(vModemTickTask,"ModemTicking",128, NULL, (tskIDLE_PRIORITY + 2UL),NULL))
	{
		#if defined (__DEBUG_ON)
		printf("ModemTicking Task created successfully.. \n");
		#endif
	}

	TRX_InitDriver();



	while(1){

		MOD_GetSignal(&signal);
		GPRS_SetSignal(signal);

		vTaskDelay(5000 / portTICK_RATE_MS);/* delay for a period of 5 minutes. */
	}
}

