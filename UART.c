//#include "UART.h"
#include "C:/Users/ahmed/Desktop/ahmed/GPIO/UART.h"


	
void UART_Init(){
	uint16_t clk_div=(int)(SYS_CLK/(9600*16));		
	float32 fraction=(float)(SYS_CLK/(9600*16))-clk_div;
	
	//ENABLE CLK FOR UART0 & ENABLE CLK FOR PORTA
	SET_BIT(SYSCTL_RCGCUART_R,0);																			  
	SET_BIT(SYSCTL_RCGCGPIO_R,0);		
	
	//DISABLE UART0
	CLEAR_BIT(UART0_CTL_R,0);																						
	UART0_IBRD_R=clk_div;																								
	UART0_FBRD_R= (int)(fraction*64+0.5);						
	
	//SET DATA SIZE 8
	UART0_LCRH_R =(UART0_LCRH_R & 0x9F)|((8-5)<<5);								
	
	//ENABLE UART0 & RX & TX
	SET_BIT(UART0_CTL_R,1);																							
	SET_BIT(UART0_CTL_R,8);																							
	SET_BIT(UART0_CTL_R,9);																				
	
	SET_BIT(GPIO_PORTA_AFSEL_R,1);
	SET_BIT(GPIO_PORTA_AFSEL_R,0);
	
	SET_BIT(GPIO_PORTA_PCTL_R,0);
	SET_BIT(GPIO_PORTA_PCTL_R,1);					
	
	SET_BIT(GPIO_PORTA_DEN_R,0);
	SET_BIT(GPIO_PORTA_DEN_R,1);
	
  CLEAR_BIT(GPIO_PORTA_AMSEL_R,0);
	CLEAR_BIT(GPIO_PORTA_AMSEL_R,1);
	
}

uint8_t UART_Receive_Char(){
	uint8_t data;
	while(BIT_IS_SET(UART0_FR_R,4)){};data=UART0_DR_R;
return data;
}


void UART_Receive_String(char *S){
	uint8_t i = 0;
	S[i] = UART_Receive_Char();
	while(S[i] != '#')
	{
		i++;
		S[i] = UART_Receive_Char();
	}
	S[i] = '\0';
}
