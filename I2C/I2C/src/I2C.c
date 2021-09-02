/*
 ============================================================================
 Name        : I2C.c
 Author      : Basmala Magdy
 Description : I2C Driver
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <I2C.h>
#include "tm4c123gh6pm.h"
#include "platform_types.h"

/*****************************************************************
*Description :  initialization the i2c                            *
* Parameter  :  1- i2c_num (0,1,2,3)
            	2- I2C_MODE {MASTER,SLAVE}
* Return : none
*****************************************************************/
void I2C_init(int8_t I2C_NUM ,uint8_t I2C_MODE)
{
	switch(I2C_NUM)
	{
		case 0:
      SYSCTL_RCGCI2C_R |= I2C0_CE;                /* enable clock to I2C */
      I2C0_MTPR_R = TPR;                          /* 100 kHz @ 16 MHz  */
      I2C0_MCR_R = I2C_MODE;                      /* The mode you want  MASTER or SLAVE   */
      break;
		case 1:
      SYSCTL_RCGCI2C_R |= I2C1_CE;                /* enable clock to I2C */
      I2C1_MTPR_R = TPR;                          /* 100 kHz @ 16 MHz  */
      I2C1_MCR_R = I2C_MODE;                      /* The mode you want  MASTER or SLAVE   */
		  break;
		case 2:
      SYSCTL_RCGCI2C_R |= I2C2_CE;                /* enable clock to I2C */
      I2C2_MTPR_R = TPR;                          /* 100 kHz @ 16 MHz  */
      I2C2_MCR_R = I2C_MODE;                      /* The mode you want  MASTER or SLAVE   */
		  break;
		case 3:
      SYSCTL_RCGCI2C_R |= I2C3_CE;                /* enable clock to I2C */
      I2C3_MTPR_R = TPR;                          /* 100 kHz @ 16 MHz  */
      I2C3_MCR_R = I2C_MODE;                      /* The mode you want  MASTER or SLAVE   */
      break;
	}
}
/************************************************************
*****Description : making sure that i2c master is not busy
     Parameter   : i2c_module_num you want to use(0,1,2,3)
*******Return : 8_bit variable error if this a problem *******
                   or zero (0) if every thing is okay
*************************************************************/
static int8_t I2C_wait_till_done(int8_t I2C_NUM)
{
	switch(I2C_NUM)
	{
		case 0:
      while( I2C0_MCS_R & 1);      /* wait until I2C master is not busy */
      return I2C0_MCS_R & 0xE;    /* return I2C error code */
		  break;

		case 1:
      while( I2C1_MCS_R & 1);      /* wait until I2C master is not busy */
      return I2C1_MCS_R & 0xE;    /* return I2C error code */
		  break;

		case 2:
      while( I2C2_MCS_R & 1);      /* wait until I2C master is not busy */
      return I2C2_MCS_R & 0xE;    /* return I2C error code */
		  break;

		case 3:
      while( I2C3_MCS_R & 1);      /* wait until I2C master is not busy */
      return I2C3_MCS_R & 0xE;    /* return I2C error code */
      break;
	}

}

/*******************************************************************
***********Description : Write one byte only ***********************

*******     Parameter  : 1-i2c_module_num you want to use(0,1,2,3)
                         2- slave address
                         3- memory addres location of the data you want
                         4- pointer to save the reading data

** return : 8_bit variable error if this a problem ******************
            or zero (0) if every thing is okay
*********************************************************************/

uint8_t I2C_byteWrite(int8_t I2C_NUM ,int8_t slaveAddr, int8_t memAddr, uint8_t data)
{
uint8_t error;
	switch(I2C_NUM)
	{
		case 0:
        I2C0_MSA_R = slaveAddr << 1;
        I2C0_MDR_R = memAddr;                 /* This byte contains the data transferred during a transaction. */
        I2C0_MCS_R = 3;                       /* The transmitted data was not acknowledged. */
        error = I2C_wait_till_done(0);        /* wait until write is complete */
        if (error) return error;

        /* sending data and waiting for ack and then sending stop */
        I2C0_MDR_R = data;                     /* loading data  in data reg*/
        I2C0_MCS_R = 5;                        /* -data-ACK-P */
        while(I2C0_MCS_R & 0x40);              /* wait until bus is not busy */
        error = I2C0_MCS_R & 0xA;              /*checking that there are no error and ack_data is received */
       if (error) return error;               /* if error is detected the func will return the error */
       return 0;                              /* no error */
		   break;

		case 1:
        /* send slave address and starting address to their regestiers  */
        I2C1_MSA_R = slaveAddr << 1;
        I2C1_MDR_R = memAddr;                 /* This byte contains the data transferred during a transaction. */

        I2C1_MCS_R = 3;                        /* The transmitted data was not acknowledged. */
        error = I2C_wait_till_done(1);        /* wait until write is complete */
        if (error) return error;

        /* sending data and waiting for ack and then sending stop */
        I2C1_MDR_R = data;                     /* loading data  in data reg*/
        I2C1_MCS_R = 5;                        /* -data-ACK-P */
        while(I2C1_MCS_R & 0x40);              /* wait until bus is not busy */
        error = I2C1_MCS_R & 0xA;              /*checking that there are no error and ack_data is recived */
       if (error) return error;               /* if error is detected the func will return the err */
       return 0;                              /* no error */
		   break;

		case 2:
        /* send slave address and starting address to their regestiers  */
        I2C2_MSA_R = slaveAddr << 1;
        I2C2_MDR_R = memAddr;

        I2C2_MCS_R = 3;
        error = I2C_wait_till_done(2);        /* wait until write is complete */
        if (error) return error;

        /* sending data and waiting for ack and then sending stop */
        I2C2_MDR_R = data;                     /* loading data  in data reg*/
        I2C2_MCS_R = 5;                        /* -data-ACK-P */
        while(I2C2_MCS_R & 0x40);              /* wait until bus is not busy */
        error = I2C2_MCS_R & 0xA;              /*checking that there are no error and ack_data is recived */
       if (error) return error;               /* if error is detected the func will return the err */
       return 0;                              /* no error */
		   break;

		case 3:
        I2C3_MSA_R = slaveAddr << 1;
        I2C3_MDR_R = memAddr;
        I2C3_MCS_R = 3;
        error = I2C_wait_till_done(3);        /* wait until write is complete */
        if (error) return error;

        I2C3_MDR_R = data;                     /* loading data  in data reg*/
        I2C3_MCS_R = 5;                        /* -data-ACK-P */
        /*error = I2C_wait_till_done(0);*/    /*this line not working (checking ack_address)      /* wait until write is complete */
        while(I2C3_MCS_R & 0x40);              /* wait until bus is not busy */
        error = I2C3_MCS_R & 0xA;              /*checking that there are no error and ack_data is received */
       if (error) return error;               /* if error is detected the func will return the err */
       return 0;                              /* no error */
		   break;
	}
}

/*****************************************************************
***********Description : Read one byte of data **********************

*******      Parameters  : 1-i2c_module_num you want to use(0,1,2,3)
                         2- slave address
                         3- memory addres location of the data you want
                         4- pointer to save the reading data

** return : 8_bit variable error if this a problem ***************
            or zero (0) if every thing is okay
******************************************************************/

uint8_t I2C_byteread(int8_t I2C_NUM ,int8_t slaveAddr, int8_t memAddr, uint8_t* data)
{
uint8_t error;

	switch(I2C_NUM)
	{
		case 0:
       /* send slave address and starting address */
       I2C0_MSA_R = slaveAddr << 1;
       I2C0_MDR_R = memAddr;
       I2C0_MCS_R = 3;                              /* S-(saddr+w)-ACK-maddr-ACK so we will send start and run */
       error = I2C_wait_till_done(0);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C0_MSA_R = (slaveAddr << 1) + 1;           /* restart: -R-(saddr+r)-ACK */
       I2C0_MCS_R = 7;                             /* -data-NACK-P so we will send repeated start and run and  stop  */

       error = I2C_wait_till_done(0);
       if (error) return error;

       *data = I2C0_MDR_R;                         /* store data received */

       while(I2C0_MCS_R & 0x40);                   /* wait until bus is not busy */
       return 0;                                  /* no error */
		   break;

		case 1:
       /* send slave address and starting address */
       I2C1_MSA_R = slaveAddr << 1;
       I2C1_MDR_R = memAddr;
       I2C1_MCS_R = 3;                              /* S-(saddr+w)-ACK-maddr-ACK so we will send start and run */
       error = I2C_wait_till_done(1);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C1_MSA_R = (slaveAddr << 1) + 1;           /* restart: -R-(saddr+r)-ACK */
       I2C1_MCS_R = 7;                             /* -data-NACK-P so we will send repeated start and run and  stop  */

       error = I2C_wait_till_done(1);
       if (error) return error;

       *data = I2C1_MDR_R;                         /* store data received */

       while(I2C1_MCS_R & 0x40);                   /* wait until bus is not busy */
       return 0;                                  /* no error */
		   break;

		case 2:
       /* send slave address and starting address */
       I2C2_MSA_R = slaveAddr << 1;
       I2C2_MDR_R = memAddr;
       I2C2_MCS_R = 3;                              /* S-(saddr+w)-ACK-maddr-ACK so we will send start and run */
       error = I2C_wait_till_done(2);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C2_MSA_R = (slaveAddr << 1) + 1;           /* restart: -R-(saddr+r)-ACK */
       I2C2_MCS_R = 7;                             /* -data-NACK-P so we will send repeated start and run and  stop  */

       error = I2C_wait_till_done(2);
       if (error) return error;

       *data = I2C2_MDR_R;                         /* store data received */

       while(I2C2_MCS_R & 0x40);                   /* wait until bus is not busy */
       return 0;                                  /* no error */
		   break;

		case 3:
       /* send slave address and starting address */
       I2C3_MSA_R = slaveAddr << 1;
       I2C3_MDR_R = memAddr;
       I2C3_MCS_R = 3;                              /* S-(saddr+w)-ACK-maddr-ACK so we will send start and run */
       error = I2C_wait_till_done(3);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C3_MSA_R = (slaveAddr << 1) + 1;           /* restart: -R-(saddr+r)-ACK */
       I2C3_MCS_R = 7;                             /* -data-NACK-P so we will send repeated start and run and  stop  */

       error = I2C_wait_till_done(3);
       if (error) return error;

       *data = I2C3_MDR_R;                         /* store data received */

       while(I2C3_MCS_R & 0x40);                   /* wait until bus is not busy */
       return 0;                                  /* no error */
		   break;

	}
}

/*******************************************************************
***********Description : Write n bytes of data ***********************

*******      Parameters  : 1-i2c_module_num you want to use(0,1,2,3)
                         2- slave address
                         3-  first memory addres location of the data
                         4- pointer to the memory location to the data


** return : 8_bit variable error if this a problem ******************
            or zero (0) if every thing is okay
*********************************************************************/

uint8_t I2C_burstWrite(int8_t I2C_NUM,int8_t slaveAddr, int8_t memAddr, int8_t byteCount, uint8_t* data)
{
	uint8_t error;

if (byteCount <= 0)
return -1;                                /* no write was performed */

switch(I2C_NUM)
{
	case 0:
      /* send slave address and starting address */
      I2C0_MSA_R = slaveAddr << 1;
      I2C0_MDR_R = memAddr;
      I2C0_MCS_R = 3;                          /* S-(saddr+w)-ACK-maddr-ACK */
      error = I2C_wait_till_done(0);          /* wait until write is complete */
      if (error) return error;

      /* send data one byte at a time */
      while (byteCount > 1)
       {
        I2C0_MDR_R = *data++;                     /* write the next byte */
        I2C0_MCS_R = 1;                           /* -data-ACK- */
        error = I2C_wait_till_done(0);      /* i have a comment in this line */
        if (error) return error;
        byteCount--;
       }

      /* send last byte and a STOP */
      I2C0_MDR_R = *data++;                    /* write the last byte */
      I2C0_MCS_R = 5;                         /* -data-ACK-P */
      error = I2C_wait_till_done(0);
      while(I2C0_MCS_R & 0x40);              /* wait until bus is not busy */
      if (error) return error;
      return 0;                            /* no error */
	    break;

	case 1:
      /* send slave address and starting address */
      I2C1_MSA_R = slaveAddr << 1;
      I2C1_MDR_R = memAddr;
      I2C1_MCS_R = 3;                          /* S-(saddr+w)-ACK-maddr-ACK */
      error = I2C_wait_till_done(1);          /* wait until write is complete */
      if (error) return error;

      /* send data one byte at a time */
      while (byteCount > 1)
       {
        I2C1_MDR_R = *data++;                     /* write the next byte */
        I2C1_MCS_R = 1;                           /* -data-ACK- */
        error = I2C_wait_till_done(1);      /* i have a comment in this line */
        if (error) return error;
        byteCount--;
       }

      /* send last byte and a STOP */
      I2C1_MDR_R = *data++;                    /* write the last byte */
      I2C1_MCS_R = 5;                         /* -data-ACK-P */
      error = I2C_wait_till_done(1);
      while(I2C1_MCS_R & 0x40);              /* wait until bus is not busy */
      if (error) return error;
      return 0;                            /* no error */
		  break;

	case 2:
      /* send slave address and starting address */
      I2C2_MSA_R = slaveAddr << 1;
      I2C2_MDR_R = memAddr;
      I2C2_MCS_R = 3;                          /* S-(saddr+w)-ACK-maddr-ACK */
      error = I2C_wait_till_done(2);          /* wait until write is complete */
      if (error) return error;

      /* send data one byte at a time */
      while (byteCount > 1)
       {
        I2C2_MDR_R = *data++;                     /* write the next byte */
        I2C2_MCS_R = 1;                           /* -data-ACK- */
        error = I2C_wait_till_done(2);      /* i have a comment in this line */
        if (error) return error;
        byteCount--;
       }

      /* send last byte and a STOP */
      I2C2_MDR_R = *data++;                    /* write the last byte */
      I2C2_MCS_R = 5;                         /* -data-ACK-P */
      error = I2C_wait_till_done(2);
      while(I2C2_MCS_R & 0x40);              /* wait until bus is not busy */
      if (error) return error;
      return 0;                            /* no error */
		  break;

  case 3:
      /* send slave address and starting address */
      I2C3_MSA_R = slaveAddr << 1;
      I2C3_MDR_R = memAddr;
      I2C3_MCS_R = 3;                          /* S-(saddr+w)-ACK-maddr-ACK */
      error = I2C_wait_till_done(3);          /* wait until write is complete */
      if (error) return error;

      /* send data one byte at a time */
      while (byteCount > 1)
       {
        I2C3_MDR_R = *data++;                     /* write the next byte */
        I2C3_MCS_R = 1;                           /* -data-ACK- */
        error = I2C_wait_till_done(3);
        if (error) return error;
        byteCount--;
       }

      /* send last byte and a STOP */
      I2C3_MDR_R = *data++;                    /* write the last byte */
      I2C3_MCS_R = 5;                         /* -data-ACK-P */
      error = I2C_wait_till_done(3);
      while(I2C3_MCS_R & 0x40);              /* wait until bus is not busy */
      if (error) return error;
      return 0;                            /* no error */
		  break;
    }
}

/*****************************************************************
***********Description : Read n bytes of data**********************

*******    Parameters  : 1- i2c_module_num you want to use(0,1,2,3)
                         2- slave address
                         3- first memory addres location of the data you want
                         4- pointer to save the reading data

** return : 8_bit variable error if this a problem ***************
            or zero (0) if every thing is okay
******************************************************************/

uint8_t I2C_burstread(int8_t I2C_NUM,int8_t slaveAddr, int8_t memAddr, int8_t byteCount, uint8_t* data)

{

	uint8_t error;

if (byteCount <= 0)
return -1; /* no read was performed */

switch(I2C_NUM)
{

 case 0 :
       /* send slave address and starting address */
       I2C0_MSA_R = slaveAddr << 1;
       I2C0_MDR_R = memAddr;
       I2C0_MCS_R = 3;

	     error = I2C_wait_till_done(0);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C0_MSA_R = (slaveAddr << 1) + 1;
       if (byteCount == 1)
       I2C0_MCS_R = 7;                               /* -data-NACK-P */
       else                                        /* else ack */
       I2C0_MCS_R = 0xB;                           /* -data-ACK- */

       error = I2C_wait_till_done(0);
       if (error) return error;

       *data++ = I2C0_MDR_R;                       /* store the data received */
       if (--byteCount == 0)                     /* if single byte read, done */
        {
         while(I2C0_MCS_R & 0x40);               /* wait until bus is not busy */
         return 0;                             /* no error */
        }

       /* read the rest of the bytes */
       while (byteCount > 1)
        {
         I2C0_MCS_R = 9;                        /* -data-ACK- */
         error = I2C_wait_till_done(0);
         if (error) return error;
         byteCount--;
         *data++ = I2C0_MDR_R;                /* store data received */
        }

       I2C0_MCS_R = 5;                       \
       error = I2C_wait_till_done(1);
       *data = I2C0_MDR_R;                   /* store data received */
       while(I2C0_MCS_R & 0x40);             /* wait until bus is not busy */
       return 0;                           /* no error */
	     break;

 case 1 :
       /* send slave address and starting address */
       I2C1_MSA_R = slaveAddr << 1;
       I2C1_MDR_R = memAddr;
       I2C1_MCS_R = 3;

	     error = I2C_wait_till_done(1);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C1_MSA_R = (slaveAddr << 1) + 1;
       if (byteCount == 1)
       I2C1_MCS_R = 7;
       else
       I2C1_MCS_R = 0xB;

       error = I2C_wait_till_done(1);
       if (error) return error;

       *data++ = I2C1_MDR_R;                       /* store the data received */
       if (--byteCount == 0)                     /* if single byte read, done */
        {
         while(I2C1_MCS_R & 0x40);               /* wait until bus is not busy */
         return 0;                             /* no error */
        }

       /* read the rest of the bytes */
       while (byteCount > 1)
        {
         I2C1_MCS_R = 9;                        /* -data-ACK- */
         error = I2C_wait_till_done(1);
         if (error) return error;
         byteCount--;
         *data++ = I2C1_MDR_R;                /* store data received */
        }

       I2C1_MCS_R = 5;
       error = I2C_wait_till_done(1);
       *data = I2C1_MDR_R;                   /* store data received */
       while(I2C1_MCS_R & 0x40);             /* wait until bus is not busy */
       return 0;                             /* no error */
       break;

	case 2 :
       /* send slave address and starting address */
       I2C2_MSA_R = slaveAddr << 1;
       I2C2_MDR_R = memAddr;
       I2C2_MCS_R = 3;

	     error = I2C_wait_till_done(2);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C2_MSA_R = (slaveAddr << 1) + 1;
       if (byteCount == 1)
       I2C2_MCS_R = 7;                               /* -data-NACK-P */
       else                                        /* else ack */
       I2C2_MCS_R = 0xB;                           /* -data-ACK- */

       error = I2C_wait_till_done(2);
       if (error) return error;

       *data++ = I2C2_MDR_R;                       /* store the data received */
       if (--byteCount == 0)                     /* if single byte read, done */
        {
         while(I2C2_MCS_R & 0x40);               /* wait until bus is not busy */
         return 0;                             /* no error */
        }

       /* read the rest of the bytes */
       while (byteCount > 1)
        {
         I2C2_MCS_R = 9;                        /* -data-ACK- */
         error = I2C_wait_till_done(2);
         if (error) return error;
         byteCount--;
         *data++ = I2C2_MDR_R;                /* store data received */
        }

       I2C2_MCS_R = 5;
       error = I2C_wait_till_done(2);
       *data = I2C2_MDR_R;                   /* store data received */
       while(I2C2_MCS_R & 0x40);             /* wait until bus is not busy */
       return 0;                           /* no error */
				break;

	case 3 :
       /* send slave address and starting address */
       I2C3_MSA_R = slaveAddr << 1;
       I2C3_MDR_R = memAddr;
       I2C3_MCS_R = 3;

	     error = I2C_wait_till_done(3);
       if (error) return error;

       /* to change bus from write to read, send restart with slave addr */
       I2C3_MSA_R = (slaveAddr << 1) + 1;
       if (byteCount == 1)
       I2C3_MCS_R = 7;
       else                                        /* else ack */
       I2C3_MCS_R = 0xB;                           /* -data-ACK- */

       error = I2C_wait_till_done(3);
       if (error) return error;

       *data++ = I2C3_MDR_R;                       /* store the data received */
       if (--byteCount == 0)                     /* if single byte read, done */
        {
         while(I2C3_MCS_R & 0x40);               /* wait until bus is not busy */
         return 0;                             /* no error */
        }

       /* read the rest of the bytes */
       while (byteCount > 1)
        {
         I2C3_MCS_R = 9;                        /* -data-ACK- */
         error = I2C_wait_till_done(3);
         if (error) return error;
         byteCount--;
         *data++ = I2C3_MDR_R;                /* store data received */
        }

       I2C3_MCS_R = 5;                        /* -data-NACK-P */
       error = I2C_wait_till_done(3);
       *data = I2C3_MDR_R;                   /* store data received */
       while(I2C3_MCS_R & 0x40);             /* wait until bus is not busy */
       return 0;                           /* no error */
				break;
  }
}
