/** @file Keypad.c
 *  @brief (agregar comentario).
 *
 *  Sensor is responsible for\n
 *  -.\n
 *  -.
 * @version		1.0
 * @date		21/03/2016
 * @author		Bioing. Martina Mauro
 * @note
 *  STGAA V3.0.0\n
 *  Facultad de Ingenieria - UNER.\n
 *  Laboratorio de prototipado Electronico &3D.\n
 *  All rights reserved. Copyright (C) 2016	.
 */

#include "board.h"
#include "Common.h"
#include "Keypad.h"

static char key;
static uint8_t rowPins[4] = {0, 1, 2, 3}; //connect to the row pinouts (P2.0 - P2.3) of the keypad
static uint8_t columnPins[2] ={4,5}; //connect to the column pinouts (P2.4 , P2.5) of the keypad
static char Keys[4][2] = {
							{ ' ','U'}, /*Up*/
							{ ' ','D'}, /*Down*/
							{ ' ','R'}, /*Right*/
							{ 'E','L'}  /*Left - Enter*/
						};

static KeypadSize size;

static void Activate_Rows(void);
static void Deactivate_Rows(void);
static void digitalWrite(uint8_t pin,uint8_t val);
static Bool digitalRead(uint8_t pin);



Status KEY_open(void)
{
	Status res=ERROR;

	size.rows = ROWS;
	size.columns = COLS;

	res=SUCCESS;
	return res;
}

Status KEY_close( void){
	Status res=ERROR;
	res=SUCCESS;
	return res;

}

// Returns the keykode of the pressed key, or NO_KEY if no key is pressed
char KEY_read(){

	key = NO_KEY; // Assume that no key is pressed, this is the default return for getKey()
	Activate_Rows();
	uint8_t r,c;

	for ( r=0; r<size.rows; r++)
	{
		digitalWrite(rowPins[r],FALSE);	// Activate the current row.

		for ( c=0; c<size.columns; c++) // Scan all the rows for a key press.
		{
			// Button pressed event.  The user pressed a button.
			if (digitalRead(columnPins[c]) == FALSE){
				digitalWrite(rowPins[r],TRUE);	// De-activate the current row.
				key = Keys[r][c];

				Deactivate_Rows();
				return key;		// Save resources and do not attempt to parse to keys at a time
			}
		}
		digitalWrite(rowPins[r],TRUE);	// De-activate the current column.
	}

	Deactivate_Rows();
	return key;
}

static void Activate_Rows(void){
	uint8_t r;
	for ( r=0; r<size.rows; r++)
	digitalWrite(r,TRUE);
}

static void Deactivate_Rows(void){
	uint8_t r;
	for ( r=0; r<size.rows; r++)
	digitalWrite(r,FALSE);
}

static void digitalWrite(uint8_t pin,uint8_t val)
{

	Chip_GPIO_SetPinState(LPC_GPIO, KEYPAD_PORT, pin, val);
}

static Bool digitalRead(uint8_t pin){

	Bool ret;
	ret=Chip_GPIO_GetPinState(LPC_GPIO, KEYPAD_PORT, pin);
	return ret;
}

/*INTERRUPT MANAGEMENT*/
void GPIO_IRQ_HANDLER(void)
{

	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIO_INTERRUPT_PORT, 3<< GPIO_INTERRUPT_PIN4);


	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(xKeyListenerSemaphore,&xHigherPriorityTaskWoken);
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);

}




