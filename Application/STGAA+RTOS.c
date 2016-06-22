/** @file STGAA+RTOS.c
 *  @brief Client program, manages the scheduler, launch all modules.
 *
 *  STGAA+RTOS is responsible for\n
 *  -.\n
 *  -.
 * @version		1.0
 * @date		14/01/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#include "Acquirer.h"
#include "Analyzer.h"
#include "UserIO.h"
#include "Storer.h"
#include "Transceiver.h"

#include "Common.h"
#include "Board.h"

/*****************************************************************************
 * Private functions
 ****************************************************************************/
/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for STGAA V3.0.0
 * @return	Nothing, function should not exit
 */
int main(void)
{

#if defined (__DEBUG_ON)
	printf("Hello World\n");
#endif

	prvSetupHardware();
	Board_Init();
	UIO_InitDriver();
	STR_InitDriver();

	if(COMM_CreateSemaphores()==ERROR) while(1);

	/* Acquiring thread */
   xTaskCreate(vAcquiringTask,"Acquiring",	configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),NULL);

	/* Monitoring thread */
   xTaskCreate(vMonitoringTask,"Monitoring",configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),NULL);

	/* Screening thread */
	xTaskCreate(vScreeningTask,"Screening",	configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),NULL);

	/* Storing thread */
	xTaskCreate(vStoringTask,"Storing",	configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),NULL);

	/* Transmitting thread */
	xTaskCreate(vTransmittingTask,"Transmitting",	configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),NULL);


	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
