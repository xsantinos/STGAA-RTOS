/** @file DSD.h
 *  @brief It handle user's input-Output, including generic display and keypad.
 *
 *  UserIO is responsible for\n
 *  -xxx.\n
 *  -xxx.
 * @version		1.0
 * @date		29/03/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#ifndef INC_DSD_H_
#define INC_DSD_H_

#include "lpc_types.h"

typedef enum{
DSD_READ,
DSD_WRITE
} DSD_MODE_T;

void DSD_TicksInput(void);
void DSD_RTC_Init(void);
int  DSD_SD_Init(void);
uint8_t DSD_GetStatus(void);

void DSD_OpenFile (char *fname,DSD_MODE_T mode);
void DSD_WriteFile(char* line);
void DSD_ReadFile (char* line);
void DSD_CloseFile(void);

void DSD_TimeStamp(void);
void DSD_MoveCursor(void);

#endif /* INC_DSD_H_ */
