/** @file UserIO.c
 *  @brief It handle user's input-Output, including generic display and keypad.
 *
 *  UserIO is responsible for\n
 *  -xxx.\n
 *  -xxx.
 * @version		1.0
 * @date		11/02/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#include "Common.h"        /*RTOS types and structures*/
#include "UserIO.h"
#include "Display.h"
#include "Keypad.h"

#include "Storer.h"
#include "Transceiver.h"

#include "Alarms.h"        /*Alarms data*/
#include "Environmental.h" /*Environmental data*/
#include "Descriptors.h"   /*Descriptors data*/


/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

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
STATIC void vRefreshingTask(void *pvParameters){

	while(1){

		/*refresh screen*/
		DSP_refresh();
		vTaskDelay(1000 / portTICK_RATE_MS);/* delay for a period of 1 seconds. */
	}

}

/*
 * @brief 		KeyListener thread
 * @param   	pvParameters is void pointer.
 * @return 		None
 */

STATIC void vKeyListenerTask(void *pvParameters){

	Bool confirma;
	char key, fila, columna, simbolo,lineas;
	simbolo='/';
	fila=0;
	columna=0;
	char* textos[LOGIN_PARAMETERS_NUM];

	/*KeyListener wait for any keypad iterrupt*/
		xSemaphoreTake(xKeyListenerSemaphore,0);


	while(1){

	xSemaphoreTake(xKeyListenerSemaphore,portMAX_DELAY);/*'Take' the semaphore blocks the task until any key are pressed */

	key= KEY_read();
	if(key=='E'){} /*llamar a la rutina de encendido/apagado*/

	switch(key){

	case 'U':	if(simbolo>='/' && simbolo<':')
				simbolo++;
				break;
	case 'D':	if(simbolo>'/' && simbolo<=':')
				simbolo--;
				break;
	case 'R':	if(columna>=0 && columna<4)
				columna++;
				simbolo='0';
				break;
	case 'L':	if(columna>0 && columna<=4)
				columna--;
				simbolo='0';
				break;
	default:	break;
	}

	if(columna<4 && fila<6){
		DSP_SetLogin(fila, columna, simbolo);
	}
	if(columna==4 && fila<6){
		fila++;
		columna=0;
		simbolo='0';
		}
	if(columna==0 && fila==6){
		DSP_ChangeWindow("Confirma");
		columna=2;
	}
	if(columna==1 && fila==6){
		DSP_ChangeWindow("Login");
		fila--;
		columna--;
	}
	if(columna==3 && fila==6){
		DSP_GetLogin(textos);/*read the recipe introduced by the user */
		STR_WriteConfig(textos,LOGIN_PARAMETERS_NUM);
		DSP_ChangeWindow("Home");
	}

	vTaskDelay(200 / portTICK_RATE_MS);/* 50 milliseconds delay. */
	}


}

/*****************************************************************************
 * Public functions
 ****************************************************************************/
void UIO_InitDriver(void){

	DSP_open();
	KEY_open();
}

/**
 * @brief 		Screening thread
 * @param   	pvParameters is void pointer.
 * @return 		None
 */
void vScreeningTask(void *pvParameters) {



	if(xTaskCreate(vRefreshingTask,"Refreshing",128, NULL, (tskIDLE_PRIORITY + 2UL),NULL))
	{
		#if defined (__DEBUG_ON)
		printf("Refreshing Task created successfully.. \n");
		#endif
	}

	if(xTaskCreate(vKeyListenerTask,"KeyListener",128, NULL, (tskIDLE_PRIORITY + 2UL),NULL))
	{
		#if defined (__DEBUG_ON)
		printf("KeyListener Task created successfully.. \n");
		#endif
	}


	while(1){
	DSP_write(); /*update environmental condition on screen*/
	//	ver donde va!!!  xSemaphoreGive( xSaveEnvironmentalSemaphore );
	}

}


