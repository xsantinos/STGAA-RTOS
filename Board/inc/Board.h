
#ifndef INC_BOARD_H_
#define INC_BOARD_H_

#include "chip.h"

/**
 * CAN Port defines
 */

#define CAN2_PORT2_PIN7_8
#define CAN_BIT_RATE 250000

/**
 * Keypad defines
 */
#define KEYPAD_PORT 2

#define ROW_0 0
#define ROW_1 1
#define ROW_2 2
#define ROW_3 3
#define COLUMN_0 4
#define COLUMN_1 5

/* GPIO pin for interrupt */
#define GPIO_INTERRUPT_PIN4     4	/* GPIO pin number mapped to interrupt */
#define GPIO_INTERRUPT_PIN5     5	/* GPIO pin number mapped to interrupt */
#define GPIO_INTERRUPT_PORT     GPIOINT_PORT2	/* GPIO port number mapped to interrupt */

/* On the LPC1769, the GPIO interrupts share the EINT3 vector. */
#define GPIO_IRQ_HANDLER  			EINT3_IRQHandler/* GPIO interrupt IRQ function name */
#define GPIO_INTERRUPT_NVIC_NAME    EINT3_IRQn	/* GPIO interrupt NVIC interrupt name */

/**
 * SD Card defines
 */

#define SD_DETECT_PORT 1
#define SD_CS_PORT 0

#define SD_DETECT_PIN 31
#define SD_CS_PIN 16

/**
 * @brief	Set up and initialize all required blocks and functions related to the board hardware.
 * @return	None
 */
void Board_Init(void);

#endif /* INC_BOARD_H_ */
