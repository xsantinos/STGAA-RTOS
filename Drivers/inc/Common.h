/*
 * Common.h
 *
 *  Created on: 25/1/2016
 *      Author: Prototipado
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include "chip.h"
#include <stdio.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

xSemaphoreHandle xEnviromentFullSemaphore;
xSemaphoreHandle xReceivedMsgSemaphore;
xSemaphoreHandle xAnalysisDoneSemaphore;
xSemaphoreHandle xKeyListenerSemaphore;

Status  COMM_CreateSemaphores(void);

#endif /* INC_COMMON_H_ */
