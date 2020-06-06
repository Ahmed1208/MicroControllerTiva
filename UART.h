#ifndef UART_H
#define UART_H
#include "tm4c123gh6pm.h"
#include "common_macros.h"
#include "stdint.h"
typedef  float float32;

//#include "std_types.h"
#define SYS_CLK		16000000


void UART_Init();
uint8_t UART_Receive_Char();
void UART_Receive_String(char *Str);


#endif
