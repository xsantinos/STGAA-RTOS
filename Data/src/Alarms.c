/** @file SensorsData.c
 *  @brief Persist sensors registered list.
 *
 *  SensorsData is responsible for\n
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

#include "Alarms.h" /*Sensors data*/

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
ALARM_T myAlarms[MAX_NUM_ALARMS];
short Alarmscount;
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
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
Status ALARM_SetAlarm(ALARM_T* pAlarm){


	myAlarms[Alarmscount].source=pAlarm->source;
	myAlarms[Alarmscount].scale=pAlarm->scale;

	Alarmscount++;
	return SUCCESS;
}

/**
 * @brief 		Acquiring thread
 * @param[in] 	CANx point to LPC_CAN_TypeDef object, should be:
 * 				- LPC_CAN1: CAN1 peripheral
 * 				- LPC_CAN2: CAN2 peripheral
 * @param[in]	baudrate: is the baud rate value will be set
 * @see publicVar()
 * @return 		None
 */
Status ALARM_GetAlarms(ALARM_T vAlarm []){

	short i;
	for(i=0;i<Alarmscount;i++){
		vAlarm[i].source=myAlarms[i].source;
		vAlarm[i].scale=myAlarms[i].scale;
	}
	return SUCCESS;
}

/**
 * @brief 		Acquiring thread
 * @param[in] 	CANx point to LPC_CAN_TypeDef object, should be:
 * 				- LPC_CAN1: CAN1 peripheral
 * 				- LPC_CAN2: CAN2 peripheral
 * @param[in]	baudrate: is the baud rate value will be set
 * @see publicVar()
 * @return 		None
 */
Status ALARM_ResetAlarms(void){
	short i;

	for(i=0;i<Alarmscount;i++){
		myAlarms[i].source=0;
		myAlarms[i].scale=0;
	}

	Alarmscount=0;

	return SUCCESS;
}


