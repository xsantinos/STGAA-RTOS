/** @file Analyzer.c
 *  @brief Evaluates the environmental condition,
 *  warning if the parameters are outside normal range.
 *
 *  Analyzer is responsible for\n
 *  -xxx.\n
 *  -xxx.
 * @version		1.0
 * @date		02/02/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#include "Common.h" /*RTOS types and structures*/
#include "Analyzer.h"

#include "Alarms.h"			/*Alarms data*/
#include "Environmental.h" 	/*Environmental data*/

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
 * @brief 		Evaluate_Ranges
 * @param[in] 	CANx point to LPC_CAN_TypeDef object, should be:
 * 				- LPC_CAN1: CAN1 peripheral
 * 				- LPC_CAN2: CAN2 peripheral
 * @param[in]	baudrate: is the baud rate value will be set
 * @see publicVar()
 * @return 		None
 */
STATIC Status Evaluate_Ranges(void){
	ENV_ENVIRONMENTAL_T myEnvironment;
	ALARM_T myAlarm;
	ENV_GetEnvironmental(&myEnvironment);

	if(myEnvironment.flow.value>FLOW_MAX_1)
	{
		myAlarm.source=FLOW;
		myAlarm.scale=LOW;

		if(myEnvironment.flow.value>FLOW_MAX_3)myAlarm.scale=HIGH;
		if(myEnvironment.flow.value>FLOW_MAX_2)myAlarm.scale=MEDIUM;
		ALARM_SetAlarm(&myAlarm);
	}

	if(myEnvironment.tyh.temperature>TEMP_MAX_1)
	{
		myAlarm.source=TEMPERATURE;
		myAlarm.scale=LOW;

		if(myEnvironment.tyh.temperature>TEMP_MAX_3)myAlarm.scale=HIGH;
		if(myEnvironment.tyh.temperature>TEMP_MAX_2)myAlarm.scale=MEDIUM;
		ALARM_SetAlarm(&myAlarm);
	}

	if(myEnvironment.tyh.humidity>HUM_MAX_1)
	{
		myAlarm.source=HUMIDITY;
		myAlarm.scale=LOW;

		if(myEnvironment.tyh.humidity>HUM_MAX_3)myAlarm.scale=HIGH;
		if(myEnvironment.tyh.humidity>HUM_MAX_2)myAlarm.scale=MEDIUM;
		ALARM_SetAlarm(&myAlarm);
	}

	if(myEnvironment.wind.speed>WSPEED_MAX_1)
	{
		myAlarm.source=WINDSPEED;
		myAlarm.scale=LOW;

		if(myEnvironment.wind.speed>WSPEED_MAX_3)myAlarm.scale=HIGH;
		if(myEnvironment.wind.speed>WSPEED_MAX_2)myAlarm.scale=MEDIUM;
		ALARM_SetAlarm(&myAlarm);
	}

	return SUCCESS;
}/*end function.*/


/*****************************************************************************
 * Public functions
 ****************************************************************************/
/**
 * @brief 		Monitoring thread
 * @param   	pvParameters is void pointer.
 * @return 		None
 */
void vMonitoringTask(void *pvParameters) {

	xSemaphoreTake(xEnviromentFullSemaphore,0);

	while(1){

		#if defined (__DEBUG_ON)
		printf("Monitoring: blocked until data arrive..\n");
		#endif

		xSemaphoreTake(xEnviromentFullSemaphore,portMAX_DELAY);/*'Take' the semaphore blocks the task until data arrive */
		Evaluate_Ranges();/*read environmental condition and evaluate normal range*/

	}

}
