#include <stdio.h>
#include <stdlib.h>
//#include "Uart.h"
#include "Uart.c"
/*******************************************************************************
 *                      Function Definition                                   *
 *******************************************************************************/
void UART_init(const UART_ConfigType *Config_Ptr);
void UART_sendByte(const uint8_t data, UART_NUMBER num);
uint8_t UART_recieveByte(UART_NUMBER num);
void UART0_Handler(void);

/*************************************************************/

extern uint8_t var_in , var_out;
int main()
{
	UART_ConfigType uart0={EIGHT_BITS,DISABLED,ONE_STOP_BIT,u0,9600};
  UART_init(&uart0);

	
		  // enable interrupt 
    UART0_ICR_R  |= 0x10; // Clear receive interrupt
    UART0_IM_R   = 0x10;
	  NVIC_EN0_R   = 0x20;             
    //NVIC_ISER_R[1] |= 0x20000000; /* enable IRQ61 for UART0 */
	
	while(1)
	{

	}
	
	
}

/*******************************************************************************
 *                      Function Decleration                                  *
 *******************************************************************************/
void UART0_Handler(void)
{
	if(UART0_IM_R == 0x10)
	{
		 var_in  = UART_recieveByte(1);
	
	   if(var_in  >= 'A' && var_in  <= 'Z')
	     {
	        	UART_sendByte(var_in  , u0);
	     }
	   else
	     {
	          var_out = var_in - 32;
		        UART_sendByte(var_out , u0);
	     }
	}
	
	 UART0_ICR_R  |= 0x10;
}
