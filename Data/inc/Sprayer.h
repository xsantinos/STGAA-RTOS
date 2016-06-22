/*
 * Sprayer.h
 *
 *  Created on: 27/4/2016
 *      Author: Prototipado
 */

#ifndef INC_SPRAYER_H_
#define INC_SPRAYER_H_

#include "lpc_types.h"

/**
 *@brief SNS configuration type definition.
 */
typedef struct{
	int  NumPadron;	/**/
	int  MatOperario;
	int  NumAsignado;
	char Propietario[20]; /**/
	char Domicilio [20];  /**/
	char Regente [20];    /**/
}SPRY_Sprayer_T;

Status SPRY_AddSprayer(SPRY_Sprayer_T* pSprayer);
Status SPRY_RemoveSprayer(SPRY_Sprayer_T* pSprayer);
Status SPRY_GetSprayer(SPRY_Sprayer_T* pSprayer);

#endif /* INC_SPRAYER_H_ */

