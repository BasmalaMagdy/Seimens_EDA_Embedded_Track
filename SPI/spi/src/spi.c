/*
 ============================================================================
 Name        : spi.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "spi.h"

#define	CS	(1U<<3)		       /* Chip Select(PF.3)*/

/*******************************************************************************
 *                       Function Declaration                                  *
 *******************************************************************************/

/******************************************************************************
 * Description : SPI_EnableChipSelect
 * Arguments   : none
 * Return      : none
 *****************************************************************************/

/*void SPI_EnableChipSelect(void)
{
	GPIO_PORTF_DATA_R &= ~CS ;
}
*/
/******************************************************************************
 * Description : SPI_DisableChipSelect
 * Arguments   : none
 * Return      : none
/ *****************************************************************************/
/*void SPI_DisableChipSelect(void)
{
	GPIO_PORTF_DATA_R |= CS ;
}*/

/******************************************************************************
 * Description : Initialize SSI0 Module, Powers ON, Configures Pins, Sets up Clock, FIFO length = 1 byte
 * Arguments   : none
 * Return      : none
 *****************************************************************************/

void init_SSIx(SPI_NUM SPIx)
{

	SYSCTL_RCGCSSI_R |= (1<<0);                                            /*Enable SSI0 Clock*/
	SYSCTL_RCGCGPIO_R |= (1<<0) | (1<<5) ;	                               /*Enable GPIOA & GPIOF Clock*/
	while (!(SYSCTL_PRGPIO_R & 0x21)) ;                                    /* wait for GPIOA to be peripheral ready*/

	if(SPIx == spi0)
	{
		/* Refer main.c for connection diagram */
		GPIO_PORTA_AFSEL_R |=  (1<<2) | (1<<3)  | (1<<4)  | (1<<5);
		GPIO_PORTA_PCTL_R  |=  (1<<9) | (1<<13) | (1<<21) | (1<<17); 		/* Pin Mux selection for SSI0*/
		GPIO_PORTA_AMSEL_R &= ~(0x3C) ; 									/* Disable Analog mode select for 2,3,4,5*/
		GPIO_PORTA_DEN_R   |=  (1<<2) | (1<<3)  | (1<<5)  | (1<<4);   		/* Digital Enable for 2,3,4,5*/
		GPIO_PORTA_DIR_R   &= ~(1<<4) ;



		SSI0_CR1_R &= ~(1<<1) ; 					                        /* Disable SSI0*/
		SSI0_CR1_R &= ~(1<<2) ; 					                        /* Master of Puppets*/

		SSI0_CC_R = (SSI0_CC_R & ~(0X0F)) + 0x00 ;		                    /* SYSCLK => Avoid modifying reserved bits*/

		/** Kick up the clock **/
		SSI0_CPSR_R = (SSI0_CPSR_R & ~(0xFF))+ 0xc8 ;		                /* 5MHz CLK = 5000000/10 ; BR=SysClk/(CPSDVSR * (1 + SCR)) 0x7D*/

		/** Enable SPI ***/
		SSI0_CR0_R = ( 0x00000007 ) ; 			                           /* SCR = 0 ; SPHA = 0 ; SPOL = 0 ; Sample on rising , shift on falling ; Freescale SPI Mode*/
		SSI0_CR1_R |= (1<<1) ; 	                                           /* Enable SSI*/
	}
	if(SPIx == spi1)
	{
		/* Refer main.c for connection diagram */
		GPIO_PORTD_AFSEL_R |=  (1<<0) | (1<<1)  | (1<<2)  | (1<<3);
		GPIO_PORTD_PCTL_R  |=  (1<<2) | (1<<5) | (1<<9) | (1<<13); 		/* Pin Mux selection for SSI1*/
		GPIO_PORTD_AMSEL_R &= ~(0x0F) ; 									/* Disable Analog mode select for 2,3,4,5*/
		GPIO_PORTD_DEN_R   |=  (1<<0) | (1<<1)  | (1<<2)  | (1<<3);   		/* Digital Enable for 2,3,4,5*/
		GPIO_PORTD_DIR_R   &= ~(1<<4) ;

		/* GPIOF Configuraion for CS */
		GPIO_PORTF_DIR_R   |=  CS;
		GPIO_PORTF_DEN_R   |=  CS;
		GPIO_PORTF_AMSEL_R &= ~CS;


		SSI1_CR1_R &= ~(1<<1) ; 					                        /* Disable SSI1*/
		SSI1_CR1_R &= ~(1<<2) ; 					                        /* Master of Puppets*/

		SSI1_CC_R = (SSI1_CC_R & ~(0X0F)) + 0x00 ;		                    /* SYSCLK => Avoid modifying reserved bits*/

		/** Kick up the clock **/
		SSI1_CPSR_R = (SSI1_CPSR_R & ~(0xFF))+ 0xc8 ;		                /* 5MHz CLK = 5000000/10 ; BR=SysClk/(CPSDVSR * (1 + SCR)) 0x7D*/

		/** Enable SPI ***/
		SSI1_CR0_R = ( 0x00000007 ) ; 			                           /* SCR = 0 ; SPHA = 0 ; SPOL = 0 ; Sample on rising , shift on falling ; Freescale SPI Mode*/
		SSI1_CR1_R |= (1<<1) ; 	                                           /* Enable SSI*/
	}
	if(SPIx == spi2)
	{
		/* Refer main.c for connection diagram */
		GPIO_PORTB_AFSEL_R |=  (1<<4) | (1<<5)  | (1<<6)  | (1<<7);
		GPIO_PORTB_PCTL_R  |=  (1<<17) | (1<<21) | (1<<25) | (1<<29); 		/* Pin Mux selection for SSI1*/
		GPIO_PORTB_AMSEL_R &= ~(0xF0) ; 									/* Disable Analog mode select for 2,3,4,5*/
		GPIO_PORTB_DEN_R   |=  (1<<4) | (1<<5)  | (1<<6)  | (1<<7);   		/* Digital Enable for 2,3,4,5*/
		GPIO_PORTB_DIR_R   &= ~(1<<4) ;


		SSI2_CR1_R &= ~(1<<1) ; 					                        /* Disable SSI2*/
		SSI2_CR1_R &= ~(1<<2) ; 					                        /* Master of Puppets*/

		SSI2_CC_R = (SSI2_CC_R & ~(0X0F)) + 0x00 ;		                    /* SYSCLK => Avoid modifying reserved bits*/

		/** Kick up the clock **/
		SSI2_CPSR_R = (SSI2_CPSR_R & ~(0xFF))+ 0xc8 ;		                /* 5MHz CLK = 5000000/10 ; BR=SysClk/(CPSDVSR * (1 + SCR)) 0x7D*/

		/** Enable SPI ***/
		SSI2_CR0_R = ( 0x00000007 ) ; 			                           /* SCR = 0 ; SPHA = 0 ; SPOL = 0 ; Sample on rising , shift on falling ; Freescale SPI Mode*/
		SSI2_CR1_R |= (1<<1) ; 	                                           /* Enable SSI*/
	}
	if(SPIx == spi3)
	{
		/* Refer main.c for connection diagram */
		GPIO_PORTD_AFSEL_R |=  (1<<0) | (1<<1)  | (1<<2)  | (1<<3);
		GPIO_PORTD_PCTL_R  |=  (1<<2) | (1<<5) | (1<<9) | (1<<13); 		/* Pin Mux selection for SSI1*/
		GPIO_PORTD_AMSEL_R &= ~(0x0F) ; 									/* Disable Analog mode select for 2,3,4,5*/
		GPIO_PORTD_DEN_R   |=  (1<<0) | (1<<1)  | (1<<2)  | (1<<3);   		/* Digital Enable for 2,3,4,5*/
		GPIO_PORTD_DIR_R   &= ~(1<<4) ;


		SSI3_CR1_R &= ~(1<<1) ; 					                        /* Disable SSI2*/
		SSI3_CR1_R &= ~(1<<2) ; 					                        /* Master of Puppets*/

		SSI3_CC_R = (SSI3_CC_R & ~(0X0F)) + 0x00 ;		                    /* SYSCLK => Avoid modifying reserved bits*/

		/** Kick up the clock **/
		SSI3_CPSR_R = (SSI3_CPSR_R & ~(0xFF))+ 0xc8 ;		                /* 5MHz CLK = 5000000/10 ; BR=SysClk/(CPSDVSR * (1 + SCR)) 0x7D*/

		/** Enable SPI ***/
		SSI3_CR0_R = ( 0x00000007 ) ; 			                           /* SCR = 0 ; SPHA = 0 ; SPOL = 0 ; Sample on rising , shift on falling ; Freescale SPI Mode*/
		SSI3_CR1_R |= (1<<1) ; 	                                           /* Enable SSI*/
	}


}


/******************************************************************************
 * Description : Transmits a byte of Data
 * Arguments   : Data to be transmitted (1 byte)
 * Return      : Transmitted Byte (required in SD Driver
 *****************************************************************************/

uint8_t SSI_Write(SPI_NUM SPIx, uint8_t data)
{
	if(SPIx == spi0)
	{
		volatile uint8_t rcv_data ;
		while((SSI0_SR_R & (1<<1))==0);  			 /* wait till Tx FIFO FULL*/
		SSI0_DR_R = data;
		while((SSI0_SR_R & (1<<2))==0);				 /* wait till Receiver Not Empty*/
		rcv_data = SSI0_DR_R ;  					 /** Read DR to clear flags and avoid bugs in any SPI Driver **/
		return data;
	}
	if(SPIx == spi1)
	{
		volatile uint8_t rcv_data ;
		while((SSI1_SR_R & (1<<1))==0);  			 /* wait till Tx FIFO FULL*/
		SSI1_DR_R = data;
		while((SSI1_SR_R & (1<<2))==0);				 /* wait till Receiver Not Empty*/
		rcv_data = SSI1_DR_R ;  					 /** Read DR to clear flags and avoid bugs in any SPI Driver **/
		return data;
	}
	if(SPIx == spi2)
	{
		volatile uint8_t rcv_data ;
		while((SSI2_SR_R & (1<<1))==0);  			 /* wait till Tx FIFO FULL*/
		SSI2_DR_R = data;
		while((SSI2_SR_R & (1<<2))==0);				 /* wait till Receiver Not Empty*/
		rcv_data = SSI2_DR_R ;  					 /** Read DR to clear flags and avoid bugs in any SPI Driver **/
		return data;
	}
	if(SPIx == spi3)
	{
		volatile uint8_t rcv_data ;
		while((SSI3_SR_R & (1<<1))==0);  			 /* wait till Tx FIFO FULL*/
		SSI3_DR_R = data;
		while((SSI3_SR_R & (1<<2))==0);				 /* wait till Receiver Not Empty*/
		rcv_data = SSI3_DR_R ;  					 /** Read DR to clear flags and avoid bugs in any SPI Driver **/
		return data;
	}

}


/******************************************************************************
 * Description : Receive a byte of Data, Transmits out 0xFF (Required in SD Inteface)
 * Arguments   : Data received (1 byte)
 * Return      : none
 *****************************************************************************/
uint8_t SSI_Read(SPI_NUM SPIx)
{
	if(SPIx == spi0)
	{
		while((SSI0_SR_R & (1<<1))==0)	;  		    /* wait till Tx FIFO FULL*/
		SSI0_DR_R = 0xFF ;
		while((SSI0_SR_R & (1<<2))==0) ;			/* wait till Receiver Not Empty*/
		return (uint8_t)SSI0_DR_R ;
	}
	if(SPIx == spi1)
	{
		while((SSI1_SR_R & (1<<1))==0)	;  		    /* wait till Tx FIFO FULL*/
		SSI1_DR_R = 0xFF ;
		while((SSI1_SR_R & (1<<2))==0) ;			/* wait till Receiver Not Empty*/
		return (uint8_t)SSI1_DR_R ;
	}
	if(SPIx == spi2)
	{
		while((SSI2_SR_R & (1<<1))==0)	;  		    /* wait till Tx FIFO FULL*/
		SSI2_DR_R = 0xFF ;
		while((SSI2_SR_R & (1<<2))==0) ;			/* wait till Receiver Not Empty*/
		return (uint8_t)SSI2_DR_R ;
	}
	if(SPIx == spi3)
	{
		while((SSI3_SR_R & (1<<1))==0)	;  		    /* wait till Tx FIFO FULL*/
		SSI3_DR_R = 0xFF ;
		while((SSI3_SR_R & (1<<2))==0) ;			/* wait till Receiver Not Empty*/
		return (uint8_t)SSI3_DR_R ;
	}

}

