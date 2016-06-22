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
#include "Display.h"
#include "Bitmaps.h"

#include "Sprayer.h"			/*GPRS data*/
#include "Recipe.h"			/*GPRS data*/
#include "GPRS.h"			/*GPRS data*/
#include "Alarms.h"			/*Alarms data*/
#include "Descriptors.h" 	/*Sensors data*/
#include "Environmental.h"	/*Environmental data*/

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
 * @brief 		ACQ_Acquiring thread
 * @param[in] 	CANx point to LPC_CAN_TypeDef object, should be:
 * 				- LPC_CAN1: CAN1 peripheral
 * 				- LPC_CAN2: CAN2 peripheral
 * @param[in]	baudrate: is the baud rate value will be set
 * @see publicVar()
 * @return 		None
 */
static Status  DSP_CreateGUI(void){
	// Window "H&T"

	GUI_Window_Create ("Login", "NONE", WHITE, "LOGIN", NULL, NULL, NULL);
	GUI_Picture_Create("Login","Login_icons",  5,23, 48, 40,InicioBitmaps,BLACK,NULL);
	GUI_Text_Create   ("Login", "row1", 60, 14, WHITE, "", BLACK, "RECETA  : ....");
	GUI_Text_Create   ("Login", "row2", 60, 22, WHITE, "", BLACK, "PRODUCTO: ....");
	GUI_Text_Create   ("Login", "row3", 60, 30, WHITE, "", BLACK, "DOSIS   : ....");
	GUI_Text_Create   ("Login", "row4", 60, 38, WHITE, "", BLACK, "VOLUMEN : ....");
	GUI_Text_Create   ("Login", "row5", 60, 46, WHITE, "", BLACK, "REGENTE : ....");
	GUI_Text_Create   ("Login", "row6", 60, 54, WHITE, "", BLACK, "OPERARIO: ....");

	GUI_Window_Create ("Confirm", "Login", WHITE, "LOGIN", NULL, NULL, NULL);
	GUI_Text_Create   ("Confirm", "Agree", 50, 25, WHITE, "", BLACK, "¿CONFIRMAR RECETA?");

	GUI_Window_Create( "Home", "NONE", WHITE, "STGAA v3.0", NULL, NULL, NULL );
	GUI_Picture_Create("Home","Signal_icons",  111, 0, 8,8,NULL,WHITE,NULL);
	GUI_Picture_Create("Home","SD_icons",  120, 0, 8,8,NULL,WHITE,NULL);

	GUI_Picture_Create("Home","GPS_icons",  3, 18, 12, 16,GpsBitmaps,BLACK,NULL);
    GUI_Text_Create   ("Home", "Latitude",  20, 16, WHITE, "", BLACK, "31*49'56.4\"S");
    GUI_Text_Create   ("Home", "Longitude",  20, 24, WHITE, "", BLACK, "60*31'20.2\"E");

    GUI_Picture_Create("Home","ANE_icons",  3, 47, 12,16,WindsBitmaps,BLACK,NULL);
    GUI_Text_Create   ("Home", "WindSpeed",  20, 40, WHITE, "", BLACK, "9.1 Km/h ");
    GUI_Text_Create   ("Home", "WindDirection",  20, 48, WHITE, "", BLACK, "NNE");

    GUI_Picture_Create("Home","CAU_icons", 77, 18, 12,16,FlowBitmaps,BLACK,NULL);
    GUI_Text_Create   ("Home", "PumpState",  90, 16, WHITE, "", BLACK, "ON");
    GUI_Text_Create   ("Home", "Flow",  90, 24, WHITE, "", BLACK, "140 L/m");

    GUI_Picture_Create("Home","TYH_icons", 77, 47, 12,16,TyhBitmaps,BLACK,NULL);
    GUI_Text_Create   ("Home", "Temperature",  90, 40, WHITE, "", BLACK, "24.5*C ");
    GUI_Text_Create   ("Home", "Humidity",  90, 48, WHITE, "", BLACK, "72 %HR ");

    GUI_Window_Draw ("Home");

	return SUCCESS;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/
Status DSP_open( void){
	GUI_DefineHeapMalloc (pvPortMalloc);
	GUI_DefineHeapFree (vPortFree);
	GUI_StartLibrary ();
	DSP_CreateGUI();
	return SUCCESS;
}


Status DSP_WriteSignal(void){
	GPRS_SIGNAL_T mySignal;
	GPRS_GetSignal(&mySignal);

	TPicture* pPicture= (TPicture*) GUI_Window_SearchObject ("Signal_icons");

	if(mySignal==MARGINAL)
			pPicture->bitmap=Signal1Bitmaps;
	if(mySignal==POOR)
			pPicture->bitmap=Signal2Bitmaps;
	if(mySignal==GOOD)
			pPicture->bitmap=Signal3Bitmaps;
	if(mySignal==EXCELLENT)
			pPicture->bitmap=Signal4Bitmaps;

	return SUCCESS;
}

Status DSP_WriteSD(BYTE stat){
	/*Detectar tarjeta: colocar icono correspondiente*/
	TPicture* pPicture= (TPicture*) GUI_Window_SearchObject ("SD_icons");
	if(stat & STA_NODISK)
		pPicture->bitmap=SdFailBitmaps;
	else
		pPicture->bitmap=SdOkBitmaps;

	return SUCCESS;
}

Status DSP_WriteEnvironmental(void){
	ENV_ENVIRONMENTAL_T myEnvironmental;
	ENV_GetEnvironmental(&myEnvironmental);

	TText* pText = (TText*) GUI_Window_SearchObject ("Latitude");
	sprintf(pText->text,"%c*%c'%3.1f\"S",myEnvironmental.gps.lat_deegres,myEnvironmental.gps.lat_minutes,myEnvironmental.gps.lat_seconds);  //"31*49'56.4\"S"

	pText = (TText*) GUI_Window_SearchObject ("Longitude");
	sprintf(pText->text,"%c*%c'%3.1f\"E",myEnvironmental.gps.long_deegres,myEnvironmental.gps.long_minutes,myEnvironmental.gps.long_seconds);// 60*31'20.2\"E

	pText = (TText*) GUI_Window_SearchObject ("WindSpeed");
	sprintf(pText->text,"%3.1f Km/h",myEnvironmental.wind.speed);  //9.1 Km/h

	pText = (TText*) GUI_Window_SearchObject ("WindDirection");
	sprintf(pText->text,"%d N",myEnvironmental.wind.direction);//NNE

	pText = (TText*) GUI_Window_SearchObject ("PumpState");
	sprintf(pText->text,"ON",myEnvironmental.flow.on_off);  //ON

	pText = (TText*) GUI_Window_SearchObject ("Flow");
	sprintf(pText->text,"%d L/m",myEnvironmental.flow.value);//140 L/m

	pText = (TText*) GUI_Window_SearchObject ("Temperature");
	sprintf(pText->text,"%3.1f *C",myEnvironmental.tyh.temperature);  //24.5*C

	pText = (TText*) GUI_Window_SearchObject ("Humidity");
	sprintf(pText->text,"%3.1f %HR",myEnvironmental.tyh.humidity);//72 %HR

	return SUCCESS;
}


Status DSP_WriteAlarm(void){

	return SUCCESS;
}


Status DSP_WriteLogin(char posX,char  posY, char simbol){

	TText* Textos[6]={	(TText*) GUI_Window_SearchObject ("row1") ,(TText*) GUI_Window_SearchObject ("row2"),
						(TText*) GUI_Window_SearchObject ("row3") ,(TText*) GUI_Window_SearchObject ("row4"),
						(TText*) GUI_Window_SearchObject ("row5") ,(TText*) GUI_Window_SearchObject ("row6")};

	char auxText[15]="";

	strncpy(auxText,Textos[posX]->text,(size_t)(10+posY));

	auxText[10+posY]=simbol;

	strncpy(Textos[posX]->text,auxText,strlen(auxText));

	return SUCCESS;
}

Status DSP_SaveLogin(void){

	TText* Textos[6]={
		(TText*) GUI_Window_SearchObject ("row1") ,(TText*) GUI_Window_SearchObject ("row2"),
		(TText*) GUI_Window_SearchObject ("row3") ,(TText*) GUI_Window_SearchObject ("row4"),
		(TText*) GUI_Window_SearchObject ("row5") ,(TText*) GUI_Window_SearchObject ("row6")
	};

	RCP_Recipe_T myRecipe;
	myRecipe.Receta  =Textos[0]->text;
	myRecipe.Producto=Textos[1]->text;
	myRecipe.Dosis   =Textos[2]->text;
	myRecipe.Volumen =Textos[3]->text;
	myRecipe.Regente =Textos[4]->text;
	myRecipe.Operario=Textos[5]->text;

	RCP_AddRecipe(&myRecipe);

	return SUCCESS;
}

Status DSP_ChangeWindow(char* name){
	GUI_Window_Draw(name);
return SUCCESS;
}

Status DSP_refresh(void){
	GUI_Window_RedrowActiveWindow();
	return SUCCESS;
}

