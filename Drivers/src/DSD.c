/** @file DSD.c
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


#include "DSD.h"
#include "board.h"

#include "diskio.h"
#include "ff.h"

#include "stdio.h"
#include "string.h"


DSTATUS stat;
DWORD p2;
WORD w1;
BYTE resul, b1;
FIL filedata;
FRESULT res;
static FATFS Fatfs[1];

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/


Bool DSD_GetSDState(void){

	Bool ret;
	ret=Chip_GPIO_GetPinState(LPC_GPIO, SD_DETECT_PORT, SD_DETECT_PIN);
	return ret;
}


/**
 * @brief
 * @param
 * @return
 */
void DSD_TicksInput(void){

	disk_timerproc();
}


/**
 * @brief
 * @param
 * @return
 */
void DSD_RTC_Init(void){

	RTC_TIME_T today;
	today.time[RTC_TIMETYPE_YEAR]=2016;
	today.time[RTC_TIMETYPE_MONTH]=4;
	today.time[RTC_TIMETYPE_DAYOFMONTH]=1;
	today.time[RTC_TIMETYPE_HOUR]=10;
	today.time[RTC_TIMETYPE_MINUTE]=22;
	today.time[RTC_TIMETYPE_SECOND]=10;

	Chip_RTC_Init(LPC_RTC);
	Chip_RTC_Enable(LPC_RTC, ENABLE);
	Chip_RTC_SetFullTime(LPC_RTC,&today);
 }

/**
 * @brief
 * @param
 * @return
 */
int DSD_SD_Init(void){

	stat = disk_initialize(0);
	if (stat & STA_NOINIT) {
#ifdef __DEBUG_ON
			printf("MMC: No Init\r\n");
#endif
		}

		if (stat & STA_NODISK) {
#ifdef __DEBUG_ON
			printf("MMC: No Disk\r\n");
#endif
		}

		if (stat != 0) {
			return 1;
		}

		resul = f_mount(0, &Fatfs[0]);
		if (resul != FR_OK) {
#ifdef __DEBUG_ON
			 printf( "Failed to mount SD %d \r\n");
#endif
		}
return 0;
}


/**
 * @brief
 * @param
 * @return
 */
uint8_t DSD_GetStatus(void){

	return (uint8_t)stat;

}


/**
 * @brief
 * @param
 * @return
 */
void DSD_OpenFile(char *fname,DSD_MODE_T mode)
{

	if(mode==DSD_READ){
			res = f_open(&filedata, fname, FA_READ);
			if(res != FR_OK){
	#ifdef __DEBUG_ON
			 		 printf("Cannot open config file for reading \r\n");
	#endif
			 	 }
			else{
				#ifdef __DEBUG_ON
		 		 printf("Open config file for reading succefull \r\n");
				#endif
			}
		}
	else {//if SD_WRITE
			res = f_open(&filedata, fname, FA_OPEN_ALWAYS|FA_WRITE);
			if(res != FR_OK){
	#ifdef __DEBUG_ON
				printf("Cannot open data file for writing \r\n");
	#endif
			 }
			else{
				#ifdef __DEBUG_ON
		 		 printf("open data file for write succefull \r\n");
				#endif
			}
	}

}

/**
 * @brief
 * @param
 * @return
 */

void DSD_CloseFile(void)
{
	DSD_TimeStamp();
	res = f_close(&filedata);

	#ifdef __DEBUG_ON
	if(res != FR_OK)
		printf("Cannot close data file \r\n");
	else
		printf("data file close succefull\r\n");
#endif

}


/**
 * @brief
 * @param
 * @return
 */
void DSD_ReadFile(char* line){
	UINT read;
	res = f_read(&filedata, line, strlen(line),&read);
}

/**
 * @brief
 * @param
 * @return
 */
void DSD_WriteFile(char* line)
{
	res = f_printf(&filedata,line);
}

/**
 * @brief
 * @param
 * @return
 */
void DSD_MoveCursor(void){

	f_lseek(&filedata, filedata.fsize);
}

/**
 * @brief
 * @param
 * @return
 */
void DSD_TimeStamp(void)
{
	RTC_TIME_T t;
	Chip_RTC_GetFullTime(LPC_RTC, &t);

	f_printf(&filedata,"\r\n");
	f_printf(&filedata,"DATE:%2d/%2d/%4d \r\n",(int)t.time[RTC_TIMETYPE_DAYOFMONTH],(int)t.time[RTC_TIMETYPE_MONTH], (int)t.time[RTC_TIMETYPE_YEAR]);
	f_printf(&filedata,"TIME:%2d:%2d:%2d \r\n",(int)t.time[RTC_TIMETYPE_HOUR],      (int)t.time[RTC_TIMETYPE_MINUTE],(int)t.time[RTC_TIMETYPE_SECOND]);
	f_printf(&filedata,"\r\n");

}
