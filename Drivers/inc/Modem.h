
/** @file Modem.h
 *  @brief Transmits the records stored in the SD memory to the remote server by GPRS.
 *
 *  Modem responsible for\n
 *  -.\n
 *  -.\n
 * @version		1.0
 * @date		29/03/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#ifndef INC_MODEM_H_
#define INC_MODEM_H_

#include "lpc_types.h"


typedef enum{
	MODEM_INIT_FAIL,


}MOD_ERROR_T;

void MOD_TicksInput(void);
void MOD_Open(void);
void MOD_GetSignal(char *signal);
void MOD_GetVersion(char *version);
void MOD_RequestHTTP(char* domain);
void MOD_RequestFTP(char* domain);
void MOD_Login(char* credentials);
void MOD_Close(void);


#endif /* INC_MODEM_H_ */
