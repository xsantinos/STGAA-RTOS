/** @file Storer.c
 *  @brief Store environmental condition and alarms.
 *
 *  Storer is responsible for\n
 *  -\n
 *  -.
 * @version		1.0
 * @date		30/03/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#include "Common.h" /*RTOS types and structures*/
#include "Storer.h" /*Sensor types and structures*/

#include "DSD.h" /*Data Storage Device types and structures*/

#include "GPRS.h"         /*data*/
#include "Alarms.h"         /*data*/
#include "Recipe.h"         /*data*/
#include "Sprayer.h"        /*data*/
#include "Environmental.h"  /*data*/

#include "string.h"
#include "stdio.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define NSAMPLES 60
char Buff_write[64];
char FileName[20];
uint8_t cont;
uint16_t data;

ENV_ENVIRONMENTAL_T	myEnvironmental;
RCP_Recipe_T	myRecipe;
SPRY_Sprayer_T	mySprayer;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
static uint16_t StringToInt(char* string);
static char AsciiToValue(char value);

static void STR_NewFile(void);
static Status STR_SetFileName(char* fname);
static Status STR_GetFileName(char* fname);

/*****************************************************************************
 * Public functions
 ****************************************************************************/

void STR_InitDriver(void){

	DSD_RTC_Init();
	DSD_SD_Init();
}

/**
 * @brief 		Refreshing thread
 * @param   	pvParameters is void pointer.
 * @return 		None
 */
static void vDiskTickTask(void *pvParameters){

	while(1){
		DSD_TicksInput();
		vTaskDelay(10 / portTICK_RATE_MS);
	}
}

/**
 * @brief
 * @param
 * @return
 */
void vStoringTask(void *pvParameters) {

	if(xTaskCreate(vDiskTickTask,"DiskTicking",128, NULL, (tskIDLE_PRIORITY + 2UL),NULL))
	{
		#if defined (__DEBUG_ON)
		printf("DiskTicking Task created successfully.. \n");
		#endif
	}

	xSemaphoreTake(xAnalysisDoneSemaphore,0);

	while(1){

		xSemaphoreTake(xAnalysisDoneSemaphore,portMAX_DELAY);/*'Take' the semaphore blocks the task until Analysis Done*/

		DSD_OpenFile("Data.txt",DSD_WRITE);
		STR_WriteHead();
		DSD_CloseFile();

	}

}

void STR_WriteHead(void){

	DSD_WriteFile("+++++++++++++++++++++++++++++++++++\r\n");
	DSD_WriteFile("+          STGAA V3.0.0           +\r\n");
	DSD_WriteFile("+                                 +\r\n");
	DSD_WriteFile("+ Lab.Prototipado Electronico &3D +\r\n");
	DSD_WriteFile("+ Facultad de Ingenieria - UNER   +\r\n");
	DSD_WriteFile("+ Todos los derechos reservados   +\r\n");
	DSD_WriteFile("+++++++++++++++++++++++++++++++++++\r\n");
	DSD_WriteFile("\r\n");
	DSD_WriteFile(">>>>>Begin Processed Data<<<<<\r\n");
	DSD_WriteFile("\r\n");

}

static Status STR_SAVE(void){

	if(cont<NSAMPLES){
		cont++;
		DSD_OpenFile(FileName,DSD_WRITE);
		DSD_MoveCursor();
	}
	else{
		cont=0;
		STR_NewFile();

	}

	ENV_GetEnvironmental(&myEnvironmental);

	sprintf((char*)Buff_write,"%3.1f *C",myEnvironmental.tyh.temperature);  //24.5*C
	sprintf((char*)Buff_write,"%c",'	');
	sprintf((char*)Buff_write,"%3.1f %HR",myEnvironmental.tyh.humidity);//72 %HR
	sprintf((char*)Buff_write,"%c",'	');
	sprintf((char*)Buff_write,"%3.1f Km/h",myEnvironmental.wind.speed);  //9.1 Km/h
	sprintf((char*)Buff_write,"%c",'	');
	sprintf((char*)Buff_write,"%d N",myEnvironmental.wind.direction);//NNE
	sprintf((char*)Buff_write,"%c",'	');
	sprintf((char*)Buff_write,"%c*%c'%3.1f\"S",myEnvironmental.gps.lat_deegres,myEnvironmental.gps.lat_minutes,myEnvironmental.gps.lat_seconds);  //"31*49'56.4\"S"
	sprintf((char*)Buff_write,"%c",'	');
	sprintf((char*)Buff_write,"%c*%c'%3.1f\"E",myEnvironmental.gps.long_deegres,myEnvironmental.gps.long_minutes,myEnvironmental.gps.long_seconds);// 60*31'20.2\"E
	sprintf((char*)Buff_write,"%c",'	');
	sprintf((char*)Buff_write,"%d L/m",myEnvironmental.flow.value);//140 L/m
	sprintf((char*)Buff_write,"%c \r\n",' ');

	DSD_WriteFile((char*)Buff_write);
	DSD_CloseFile();

	return SUCCESS;
}

/*Cierra el archivo para guardar lo escrito, abre un archivo nuevo con el sufijo del nombre incrementado*/
static void STR_NewFile(void){

	char BuffAux[20];
	SPRY_GetSprayer(&mySprayer);
	RCP_GetRecipe(&myRecipe);

	DSD_CloseFile();
	data++;

	uint16_t NRecipe=StringToInt(myRecipe.Receta);

	sprintf((char*)BuffAux,"%dp_%dr_%dd.txt",mySprayer.NumAsignado,NRecipe,data);

	DSD_OpenFile((char*)BuffAux,DSD_WRITE);
	STR_SetFileName(BuffAux);

}

void STR_WriteFileSent(char* line){

	DSD_OpenFile("SystemConfig.txt",DSD_WRITE);
	DSD_WriteFile(line);
	DSD_CloseFile();
}


static uint16_t StringToInt(char* string){

	uint16_t res;
	char lenght=strlen(string);

	if(lenght==1){
		res= (uint16_t) AsciiToValue(string[0]);
	}

	if(lenght==2){
		res= (uint16_t) (AsciiToValue(string[0]) +AsciiToValue(string[1])*10);
	}

	if(lenght==3){
		res= (uint16_t) (AsciiToValue(string[0]) +AsciiToValue(string[1])*10 +AsciiToValue(string[2])*100);
	}
	if(lenght==4){
		res= (uint16_t) (AsciiToValue(string[0]) +AsciiToValue(string[1])*10 +AsciiToValue(string[2])*100 +AsciiToValue(string[3])*1000);
	}

	return res;
}

static char AsciiToValue(char value)
{/////AsciiToValue/////// Una funcion que nos devuelva el valor del char de entrada
	char aux1=0;
	if(value < 0x40) //es un numero le resto 0x30
	{
		aux1=value - 0x30;
		return aux1;
	}
	else
	{
		aux1= value -0x41+0x0A ; //es una letra, le resto 0x41 y le sumo 0x0A
		return aux1;
	}
}


STR_RestoreFiles(){
//001p_012r_003d.txt
	char BuffAux[20];
	char * pfound=NULL;
	DSD_OpenFile("SystemConfig.txt",DSD_READ);
	DSD_ReadFile(BuffAux);
	pfound = strstr(BuffAux,"p_");
	if (pfound) {
		strncpy(FileName, (found+11),3);
	}

}


/**
 * @brief
 * @param[in]
 * @see
 * @return
 */
static Status STR_SetFileName(char* fname){

	strcpy(FileName,fname);
	return SUCCESS;
}

/**
 * @brief
 * @param[in]
 * @see
 * @return
 */
static Status STR_GetFileName(char* fname){

	strcpy(fname,FileName);
	return SUCCESS;
}

