/*
 * Storer.h
 *
 *  Created on: 29/3/2016
 *      Author: Prototipado
 */

#ifndef INC_STORER_H_
#define INC_STORER_H_

void vStoringTask(void *pvParameters) ;

void STR_InitDriver(void);
void STR_SaveData(void);
void STR_WriteTime(void);
void STR_WriteHead(void);
void STR_WriteConfig(char* txt [],char size);
Bool STR_getState(void);


#endif /* INC_STORER_H_ */



