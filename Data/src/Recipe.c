/** @file Recipe.c
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

#include "Recipe.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
RCP_Recipe_T myRecipe;
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
Status RCP_AddRecipe(RCP_Recipe_T* pRecipe){
	myRecipe.Operario=pRecipe->Operario;
	myRecipe.Regente =pRecipe->Regente;
	myRecipe.Receta	 =pRecipe->Receta;
	myRecipe.Producto=pRecipe->Producto;
	myRecipe.Dosis	 =pRecipe->Dosis;
	myRecipe.Volumen =pRecipe->Volumen;
}

/**
 * @brief
 * @param
 * @see
 * @return
 */
Status RCP_RemoveRecipe(RCP_Recipe_T* pRecipe){

}

/**
 * @brief
 * @param
 * @see
 * @return
 */
Status RCP_GetRecipe(RCP_Recipe_T* pRecipe){
	pRecipe->Operario	=myRecipe.Operario;
	pRecipe->Regente	=myRecipe.Regente;
	pRecipe->Receta		=myRecipe.Receta;
	pRecipe->Producto	=myRecipe.Producto;
	pRecipe->Dosis		=myRecipe.Dosis;
	pRecipe->Volumen	=myRecipe.Volumen;
}
