/** @file EnvironmentalData.c
 *  @brief Persist environmental condition.
 *
 *  SensorsData is responsible for\n
 *  - \n
 *  - .
 * @version		1.0
 * @date		14/01/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#include "Environmental.h" /*Environmental data*/

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
ENV_ENVIRONMENTAL_T myEnvironmental;

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
Status ENV_SetEnvironmental(ENV_ENVIRONMENTAL_T* pEnvironment){


	myEnvironmental.flow.on_off=pEnvironment->flow.on_off;
	myEnvironmental.flow.value=pEnvironment->flow.value;
	myEnvironmental.gps.lat_deegres=pEnvironment->gps.lat_deegres;
	myEnvironmental.gps.lat_minutes=pEnvironment->gps.lat_minutes;
	myEnvironmental.gps.lat_seconds=pEnvironment->gps.lat_seconds;
	myEnvironmental.gps.long_deegres=pEnvironment->gps.long_deegres;
	myEnvironmental.gps.long_minutes=pEnvironment->gps.long_minutes;
	myEnvironmental.gps.long_seconds=pEnvironment->gps.long_seconds;
	myEnvironmental.tyh.humidity=pEnvironment->tyh.humidity;
	myEnvironmental.tyh.temperature=pEnvironment->tyh.temperature;
	myEnvironmental.wind.direction=pEnvironment->wind.direction;
	myEnvironmental.wind.speed=pEnvironment->wind.speed;

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
Status ENV_GetEnvironmental(ENV_ENVIRONMENTAL_T* pEnvironment){

	pEnvironment->flow.on_off=myEnvironmental.flow.on_off;
	pEnvironment->flow.value=myEnvironmental.flow.value;
	pEnvironment->gps.lat_deegres=myEnvironmental.gps.lat_deegres;
	pEnvironment->gps.lat_minutes=myEnvironmental.gps.lat_minutes;
	pEnvironment->gps.lat_seconds=myEnvironmental.gps.lat_seconds;
	pEnvironment->gps.long_deegres=myEnvironmental.gps.long_deegres;
	pEnvironment->gps.long_minutes=myEnvironmental.gps.long_minutes;
	pEnvironment->gps.long_seconds=myEnvironmental.gps.long_seconds;
	pEnvironment->tyh.humidity=myEnvironmental.tyh.humidity;
	pEnvironment->tyh.temperature=myEnvironmental.tyh.temperature;
	pEnvironment->wind.direction=myEnvironmental.wind.direction;
	pEnvironment->wind.speed=myEnvironmental.wind.speed;

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
Status ENV_ResetEnvironmental(void){

	myEnvironmental.flow.on_off=0;
	myEnvironmental.flow.value=0;
	myEnvironmental.gps.lat_deegres=0;
	myEnvironmental.gps.lat_minutes=0;
	myEnvironmental.gps.lat_seconds=0;
	myEnvironmental.gps.long_deegres=0;
	myEnvironmental.gps.long_minutes=0;
	myEnvironmental.gps.long_seconds=0;
	myEnvironmental.tyh.humidity=0;
	myEnvironmental.tyh.temperature=0;
	myEnvironmental.wind.direction=0;
	myEnvironmental.wind.speed=0;

	return SUCCESS;
}
