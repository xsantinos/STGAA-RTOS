/** @file Acquirer.c
 *  @brief Acquires signals from sensors.
 *
 *  Acquirer is responsible for\n
 *  -Read data.\n
 *  -Send data.
 * @version		1.0
 * @date		14/01/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#include "Common.h" /*RTOS types and structures*/
#include "Sensor.h" /*Sensor types and structures*/
#include "Acquirer.h"
#include "Descriptors.h" /*Sensors data*/

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
CAN_MSG_T RcvMsgBuf;
DSC_DESCRIPTOR_T SensorsList;
char ReceivedCount;
char sensors_currently_registered;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/**
 * @brief 		Acquiring thread
 * @param[in] 	CANx point to LPC_CAN_TypeDef object, should be:
 * 				- LPC_CAN1: CAN1 peripheral
 * 				- LPC_CAN2: CAN2 peripheral
 * @param[in]	baudrate: is the baud rate value will be set
 * @see publicVar()
 * @return 		None
 */
STATIC Status AskForData(void){

	SNS_MSG_T myOutMsg;
	DSC_DESCRIPTOR_T myDescriptor;

	if(DSC_GetSensorListLength()!=FALSE)
	{
		DSC_ResetSensorsList(); /*The list must be updated.*/
	}
	myOutMsg.head.ID=ID_CPU;
	myOutMsg.head.CMD=CMD_STATE;
	SNS_write(&myOutMsg);

	vTaskDelay(5000 / portTICK_RATE_MS);/* delay for a period of 1 seconds..waiting for sensors. */

	if(DSC_GetSensorListLength()!=FALSE)
	{
		myOutMsg.head.ID=ID_CPU;
		myOutMsg.head.CMD=CMD_DATA;
		SNS_write(&myOutMsg);
	}
	else
	{
		#if defined (__DEBUG_ON)
		printf("ERROR sensors don't respond.. \n");
		#endif
	}

	return SUCCESS;
}/*end function.*/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief 		Acquiring thread
 * @param   	pvParameters is void pointer.
 * @return 		None
 */
void vAcquiringTask(void *pvParameters) {

	if(xTaskCreate(vSnsHandlerTask,"SnsHandler",128, NULL, (tskIDLE_PRIORITY + 2UL),NULL)==pdTRUE)
	{
		#if defined (__DEBUG_ON)
		printf("SnsHandler Task created successfully.. \n");
		#endif
	}

	while(1){

//		AskForData(); /*lee lista de sensores activos y solicita datos*/
		vTaskDelay(5000 / portTICK_RATE_MS);/* delay for a period of 5 seconds. */
	}

}
