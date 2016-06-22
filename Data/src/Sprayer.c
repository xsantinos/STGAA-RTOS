/** @file Sprayer.c
 *  @brief Persist sensors registered list.
 *
 *  is responsible for\n

 * @version		1.0
 * @date		14/01/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#include "Sprayer.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
SPRY_Sprayer_T mySprayer;
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
 * @brief
 * @param
 * @see
 * @return
 */
Status SPRY_AddSprayer(SPRY_Sprayer_T* pSprayer){
	mySprayer.Domicilio=pSprayer->Domicilio;
	mySprayer.MatOperario=pSprayer->MatOperario;
	mySprayer.NumAsignado=pSprayer->NumAsignado;
	mySprayer.NumPadron=pSprayer->NumPadron;
	mySprayer.Propietario=pSprayer->Propietario;
	mySprayer.Regente=pSprayer->Regente;
	return SUCCESS;
}

/**
 * @brief
 * @param
 * @see
 * @return
 */
Status SPRY_RemoveSprayer(SPRY_Sprayer_T* pSprayer){

}

/**
 * @brief
 * @param
 * @see
 * @return
 */
Status SPRY_GetSprayer(SPRY_Sprayer_T* pSprayer){

	pSprayer->Domicilio=mySprayer.Domicilio;
	pSprayer->MatOperario=mySprayer.MatOperario;
	pSprayer->NumAsignado=mySprayer.NumAsignado;
	pSprayer->NumPadron=mySprayer.NumPadron;
	pSprayer->Propietario=mySprayer.Propietario;
	pSprayer->Regente=mySprayer.Regente;

return SUCCESS;
}
