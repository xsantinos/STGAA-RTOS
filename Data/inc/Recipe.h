/*
 * Recipe.h
 *
 *  Created on: 27/4/2016
 *      Author: Prototipado
 */

#ifndef INC_RECIPE_H_
#define INC_RECIPE_H_

#include "lpc_types.h"

/**
 *@brief
 */
typedef struct{
	char Receta   [5]; /* */
	char Producto [5]; /* */
	char Dosis    [5]; /* */
	char Volumen  [5]; /* */
	char Operario [5]; /* */
	char Regente  [5]; /* */
}RCP_Recipe_T;

Status RCP_AddRecipe(RCP_Recipe_T* pRecipe);
Status RCP_RemoveRecipe(RCP_Recipe_T* pRecipe);
Status RCP_GetRecipe(RCP_Recipe_T* pRecipe);

#endif /* INC_RECIPE_H_ */
