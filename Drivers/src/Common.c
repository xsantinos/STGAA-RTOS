/*
 * common.c
 *
 *  Created on: 25/1/2016
 *      Author: Prototipado
 */

#include "Common.h"
#include "Sensor.h"

/* Create the queues used by the modules  */
Status  COMM_CreateSemaphores(void) {

	vSemaphoreCreateBinary(xEnviromentFullSemaphore);
	vSemaphoreCreateBinary(xReceivedMsgSemaphore);
	vSemaphoreCreateBinary(xAnalysisDoneSemaphore);
	vSemaphoreCreateBinary(xKeyListenerSemaphore);

	return SUCCESS;
}

