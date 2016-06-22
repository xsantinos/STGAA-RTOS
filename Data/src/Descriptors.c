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

#include "Descriptors.h" /*Sensors data*/

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
short RegisteredSensorCount=0;
short Stack_index=0;

DSC_DESCRIPTOR_T SensorsList[MAX_NUM_SNS];

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
void ClearListItem(short index){
SensorsList[index].id=0;
SensorsList[index].config.FREQ=0;
SensorsList[index].config.MODE=0;
SensorsList[index].config.RESOL=0;
SensorsList[index].state=0;
}
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
Status DSC_AddSensorToList(DSC_DESCRIPTOR_T* pDescriptor){


	if(RegisteredSensorCount<MAX_NUM_SNS)
	{
		SensorsList[RegisteredSensorCount].id=pDescriptor->id;
		SensorsList[RegisteredSensorCount].config.FREQ=pDescriptor->config.FREQ;
		SensorsList[RegisteredSensorCount].config.MODE=pDescriptor->config.MODE;
		SensorsList[RegisteredSensorCount].config.RESOL=pDescriptor->config.RESOL;
		SensorsList[RegisteredSensorCount].state=pDescriptor->state;
		RegisteredSensorCount++;
		Stack_index=RegisteredSensorCount;
	}
	else
	{
		return ERROR;
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
Status DSC_RemoveSensorFromList(DSC_DESCRIPTOR_T* pDescriptor){

	short i;

	for(i=0;i<MAX_NUM_SNS;i++){
		if(SensorsList[i].id==pDescriptor->id)
		{
            ClearListItem(i);
            RegisteredSensorCount--;
            Stack_index=RegisteredSensorCount;
		}
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
Status DSC_ResetSensorsList(void){

	char i;

	for(i=0;i<MAX_NUM_SNS;i++){
		ClearListItem(i);
	}
	RegisteredSensorCount=0;
	Stack_index=RegisteredSensorCount;

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
Status DSC_GetSensorFromList(DSC_DESCRIPTOR_T* pDescriptor){

	if(Stack_index>0){
	SensorsList[Stack_index].id=pDescriptor->id;
	SensorsList[Stack_index].config.FREQ=pDescriptor->config.FREQ;
	SensorsList[Stack_index].config.MODE=pDescriptor->config.MODE;
	SensorsList[Stack_index].config.RESOL=pDescriptor->config.RESOL;
	SensorsList[Stack_index].state=pDescriptor->state;
	Stack_index--;
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
short DSC_GetSensorListLength(void){

	return RegisteredSensorCount;
}
