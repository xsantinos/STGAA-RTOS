/** @file Sensor.c
 *  @brief (agregar comentario).
 *
 *  Sensor is responsible for\n
 *  -.\n
 *  -.
 * @version		1.0
 * @date		20/01/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#include "Common.h"
#include "Board.h"
#include "Sensor.h"
#include "Descriptors.h" /*Sensors data*/
#include "Environmental.h" /*Environmental data*/

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

CAN_MSG_T RcvMsgBuf,SendMsgBuf;
char ReceivedDataCount =0;
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/**
 * @brief 		ACQ_Acquiring thread
 * @param[in] 	CANx point to LPC_CAN_TypeDef object, should be:
 * 				- LPC_CAN1: CAN1 peripheral
 * 				- LPC_CAN2: CAN2 peripheral
 * @param[in]	baudrate: is the baud rate value will be set
 * @see publicVar()
 * @return 		None
 */
STATIC Status SNS_DataUnwrap(CAN_MSG_T * pReceivedMsg, ENV_ENVIRONMENTAL_T *  pEnvironmental){

/*CAN id_standard has 11 bits, should be read according to the format xxxyyyyzzzz.
 * xxx: Unused; yyyy:identifier; zzzz:command; */
	switch(pReceivedMsg->ID>>4)
	{
	case ID_GPS:  pEnvironmental->gps.lat_deegres=pReceivedMsg->Data[0];
					  pEnvironmental->gps.lat_minutes=pReceivedMsg->Data[1];
					  pEnvironmental->gps.lat_seconds=((pReceivedMsg->Data[2])*256 +(pReceivedMsg->Data[3]))*0.006;
					  pEnvironmental->gps.long_deegres=pReceivedMsg->Data[4];
					  pEnvironmental->gps.long_minutes=pReceivedMsg->Data[5];
					  pEnvironmental->gps.long_seconds=((pReceivedMsg->Data[6])*256 +(pReceivedMsg->Data[7]))*0.006;
					  break;
	case ID_ANEMOMETER:
					  pEnvironmental->wind.speed=((pReceivedMsg->Data[0])*256 +(pReceivedMsg->Data[1]))*0.01;
					  pEnvironmental->wind.direction=((pReceivedMsg->Data[2])*256 +(pReceivedMsg->Data[3]));
					  break;
	case ID_THERMOHYGROMETER:
					  pEnvironmental->tyh.temperature=((pReceivedMsg->Data[0])*256 +(pReceivedMsg->Data[1]))*0.01;
					  pEnvironmental->tyh.humidity=((pReceivedMsg->Data[2])*256 +(pReceivedMsg->Data[3]))*0.01;
					  break;
	case ID_FLOWMETER:
					  pEnvironmental->flow.value=((pReceivedMsg->Data[0])*256 +(pReceivedMsg->Data[1]));
					  pEnvironmental->flow.on_off=pReceivedMsg->Data[2];
					  break;

	default :		  return ERROR;
	}

return SUCCESS;
}

STATIC Status SNS_DescriptorUnwrap(CAN_MSG_T * pReceivedMsg, DSC_DESCRIPTOR_T *  pDescriptor){

	pDescriptor->id=(pReceivedMsg->ID>>4);
	pDescriptor->config.FREQ=pReceivedMsg->Data[0];
	pDescriptor->config.MODE=pReceivedMsg->Data[1];
	pDescriptor->config.RESOL=pReceivedMsg->Data[2];
    pDescriptor->state=pReceivedMsg->Data[3];

    return SUCCESS;
}



/*****************************************************************************
 * Public functions
 ****************************************************************************/


Status SNS_read (SNS_MSG_T *  InMsg){


	return  SUCCESS;
}

Status SNS_write(SNS_MSG_T *  myOutMsg){

	CAN_BUFFER_ID_T   TxBuf;

	SendMsgBuf.ID = (myOutMsg->head.ID<<4)+(myOutMsg->head.CMD);

	if(myOutMsg->head.CMD==CMD_CONFIG)
	{
			/*Put here the code to configure the sensors.*/
	}

	taskENTER_CRITICAL();
	{
	TxBuf = Chip_CAN_GetFreeTxBuf(LPC_CAN2);
	Chip_CAN_Send(LPC_CAN2, TxBuf, &SendMsgBuf);
	}
	taskEXIT_CRITICAL();
	while ((Chip_CAN_GetStatus(LPC_CAN2) & CAN_SR_TCS(TxBuf)) == 0) {}

	return  SUCCESS;
}

void CAN_IRQHandler( void )
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	uint32_t IntStatus;

	IntStatus = Chip_CAN_GetIntStatus(LPC_CAN2);

	if (IntStatus & CAN_ICR_RI)
	{	/* New Message came */
		Chip_CAN_Receive(LPC_CAN2, &RcvMsgBuf);
		/*'Give' the semaphore to unblock the handler*/
		xSemaphoreGiveFromISR(xReceivedMsgSemaphore,&xHigherPriorityTaskWoken);
	}
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

void vSnsHandlerTask( void *pvParameters ){

	DSC_DESCRIPTOR_T myDescriptor;
	ENV_ENVIRONMENTAL_T myEnvironmental;

	xSemaphoreTake(xReceivedMsgSemaphore,0);

	while(1){

		/*'Take' the semaphore blocks the handler until an interrupt arrive */
		xSemaphoreTake(xReceivedMsgSemaphore,portMAX_DELAY);

		if((RcvMsgBuf.ID&0x0F)==CMD_CONFIG)
		{
				SNS_DescriptorUnwrap(&RcvMsgBuf,&myDescriptor);
				DSC_AddSensorToList(&myDescriptor);
		}
		else
		{
				SNS_DataUnwrap(&RcvMsgBuf,&myEnvironmental);
				ReceivedDataCount++;
				if(ReceivedDataCount==DSC_GetSensorListLength())
				{
					ReceivedDataCount=0;
					ENV_SetEnvironmental(&myEnvironmental);

					/*'Give' the semaphore to unblock the task*/
					xSemaphoreGive(xEnviromentFullSemaphore);
				}
		}
	}
}
