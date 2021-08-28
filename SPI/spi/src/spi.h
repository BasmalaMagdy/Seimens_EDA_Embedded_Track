/*
 * spi.h
 *
 */
#ifndef _spi_h
#define _spi_h

#include "platform_types.h"
#include "tm4c123gh6pm.h"



/* The UART number you want to work on */
typedef enum
{
    spi0,spi1,spi2,spi3
}SPI_NUM;


 /*******************************************************************************
  *                      Functions Prototypes                                   *
  *******************************************************************************/

//void SPI_EnableChipSelect(void);
//void SPI_DisableChipSelect(void) ;
void init_SSIx(SPI_NUM SPIx)
uint8_t SSI_Write(SPI_NUM SPIx,uint8_t data) ;
uint8_t SSI_Read(SPI_NUM SPIx) ;


#endif
