#ifndef GPIO_H_
#define GPIO_H_

#include "common_macros.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include <assert.h>


#define High 1
#define high 1
#define Low 0
#define low 0

typedef enum {
	PortA=0 ,PortB ,PortC ,PortD ,PortE ,PortF
}PORT;

typedef enum {
	Input,Output
}MODE;

typedef enum {
	P0,P1,P2,P3,P4,P5,P6,P7
}PIN;

void pinMode( PORT Port, PIN Pin, MODE Mode );
void digitalWrite(PORT Port, PIN Pin, bool Value);
bool digitalPinRead(PORT Port, PIN Pin);
uint8_t digitalPortRead(PORT Port);
void digitalPortWrite(PORT Port, uint8_t Value);


#endif
