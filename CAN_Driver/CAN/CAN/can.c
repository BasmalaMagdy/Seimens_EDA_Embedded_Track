/********************************************************************************
 * File Name: can.c
 *
 * Author: Basmala Magdy
 *
 * Created on: Sep 5, 2021
 *
 * Description: CAN driver
 *******************************************************************************/

/*****************************************************************************************************************
 * *****************************                 INCLUDES                    *************************************
 * ***************************************************************************************************************/

#include "std_types.h"
#include "tm4c123gh6pm.h"
#include "can.h"

/*********************************************************************************************************************
 *                                                Functions Definitions                                              *
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Description : Can initialization
 * Parameters  : can_configuration
 * Return      : None
 * *******************************************************************************************************************/

void CANX_INIT(CAN_Config *config)
{
    CANx_PIN_INIT(config);                                 /*Call CAN Pin initialization Function*/
    if(config->can_mode == CAN_0)
    {
        CAN0_CTL_R |= CAN_CTL_INIT | CAN_CTL_CCE ;         /* Initialization and Configuration Change Enable Can0 CTL Register P = 1060*/
        while(CAN0_IF1CRQ_R & 0x00008000); //wait while CAN0 Module is BUSY

        CANx_TIME_BIT(config);                             /* Call CAN Time bits*/
        CAN0_CTL_R &= ~ CAN_CTL_INIT;                      /*Disable Can0 CTL Register*/
    }
    else if(config->can_mode == CAN_1)
    {
        CAN1_CTL_R |= CAN_CTL_INIT | CAN_CTL_CCE ;         /* Initialization and Configuration Change Enable Can1 CTL Register P = 1060*/
        while(CAN1_IF1CRQ_R & 0x00008000); //wait while CAN0 Module is BUSY

        CANx_TIME_BIT(config);                             /* Call CAN Time bits*/
        CAN1_CTL_R &= ~ CAN_CTL_INIT;                      /*Disable Can0 CTL Register*/
    }
}

/*********************************************************************************************************************
 * Description : Initialization for can pins
 * Parameters  : can_configuration
 * Return      : None
 * *******************************************************************************************************************/
void CANx_PIN_INIT(CAN_Config *config)
{
    /*                       can configuration for CAN0                    */
    if(config->can_mode == CAN_0)
    {
        uint16_t delay;                                      /* delay variable to delay after enable Port clock */
        RCGC0_CLOCK_MODE|=(1<< can0);                        /*enable the can clock of the module CAN0 pin = 24  ,p= 457*/

        /*                 Port B Register Configuration                   */
        if(config->can_port == B)
        {
            RCGC2_CLOCK_PORT|=(1<< GPIOB);                   /*enable  the clock of portB RX = PB4 TX = PB5 ,p=465*/
            delay = RCGC2_CLOCK_PORT;
            GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;               /* Activate Port B */
            GPIO_PORTB_CR_R |= 0x30;                         /* commit register*/
            GPIO_PORTB_AMSEL_R &= ~0x30;                     /* analog mode select for port B*/
            GPIO_PORTB_PCTL_R &= ~ 0x00ff0000;               /* determine the selected alternate function*/
            GPIO_PORTB_AFSEL_R |=  0x30  ;                   /* alternate function select*/
            GPIO_PORTB_DEN_R |= 0x30;                        /* digital enable*/
            GPIO_PORTB_DIR_R |= 0x20;                        /* Configure the control pin PB5 as output pin*/
            GPIO_PORTB_DATA_R &= ~0x30;                      /* digital enable*/
        }

        /*                 Port E Register Configuration                   */
        if(config->can_port == E)
        {
            RCGC2_CLOCK_PORT|=(1<<GPIOE);                    /*enable  the clock of portB RX = PE4 TX = PE5 p=465*/
            delay = RCGC2_CLOCK_PORT;
            GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;               /* Activate Port E */
            GPIO_PORTE_CR_R |= 0x30;                         /* commit register*/
            GPIO_PORTE_AMSEL_R &= ~0x30;                     /* analog mode select for port E*/
            GPIO_PORTE_PCTL_R &= ~ 0x00ff0000;               /* determine the selected alternate function*/
            GPIO_PORTE_AFSEL_R |=  0x30 ;                     /* alternate function select*/
            GPIO_PORTE_DEN_R |= 0x30;                        /* digital enable*/
            GPIO_PORTE_DIR_R |= 0x20;                        /* Configure the control pin PE5 as output pin*/
            GPIO_PORTE_DATA_R &= ~0x30;                      /* digital enable*/
        }

        /*                 Port F Register Configuration                   */
        if(config->can_port == F)
        {
            RCGC2_CLOCK_PORT|=(1<<GPIOF);                   /*enable  the clock of portB RX = PE4 TX = PE5 p=465*/
            delay = RCGC2_CLOCK_PORT;
            GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;              /* Activate Port F */
            GPIO_PORTF_CR_R |= 0x09;                        /* commit register*/
            GPIO_PORTF_AMSEL_R &= ~ 0x09;                   /* analog mode select for port F*/
            GPIO_PORTF_PCTL_R &= ~ 0x0000f00f;              /* determine the selected alternate function*/
            GPIO_PORTF_AFSEL_R |=  0x09;                    /* alternate function select*/
            GPIO_PORTF_DEN_R |= 0x09;                       /* digital enable*/
            GPIO_PORTF_DIR_R |= 0x08;                       /* Configure the control pin PF3 as output pin*/
            GPIO_PORTF_DATA_R &= ~ 0x09;                    /* digital enable*/
        }

    }

    /*                       can configuration for CAN1                    */
    if(config->can_mode == CAN_1)
    {
        uint16_t delay;
        RCGC0_CLOCK_MODE|=(1<< can1);                     /*enable the can clock of the module CAN1 pin = 25 ,p= 457 p=465*/

        /*                 Port A Register Configuration                   */
        if(config->can_port == A)
        {
            RCGC2_CLOCK_PORT|=(1<<GPIOA);                   /*enable  the clock of portB RX = PE4 TX = PE5 p=465*/
            delay = RCGC2_CLOCK_PORT;
            GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;              /* Activate Port A */
            GPIO_PORTA_CR_R |= 0x03;                        /* commit register*/
            GPIO_PORTA_AMSEL_R &= ~ 0x03;                   /* analog mode select for port A*/
            GPIO_PORTA_PCTL_R &= ~ 0x000000ff;              /* determine the selected alternate function*/
            GPIO_PORTA_AFSEL_R |=  0x03;                    /* alternate function select*/
            GPIO_PORTA_DEN_R |= 0x03;                       /* digital enable*/
            GPIO_PORTA_DIR_R |= 0x02;                       /* Configure the control pin PA1 as output pin*/
            GPIO_PORTA_DATA_R &= ~ 0x03;                    /* digital enable*/
        }

    }
}

/*********************************************************************************************************************
 * Description : Can time bits initialization  p.1063  p 1076
 *               BRP  :  Baud Rate Prescaler
 *               SJW  :  (Re)Synchronization Jump Width
 *               TSEG1:  Time Segment Before Sample Point
 *               TSEG2:  Time Segment after Sample Point
 * Parameters  : can_configuration
 * Return      : None
 * *******************************************************************************************************************/

void CANx_TIME_BIT(CAN_Config *config)
{
    /* CANBIT Register Field Setting */
    if(config->can_mode == CAN_0)
    {
        CAN0_BIT_R |= config->bit_time.BRP | (config->bit_time.SJW <<6) | (config->bit_time.TSEG1 <<8) | (config->bit_time.TSEG2 <<12);
    }
    else if(config->can_mode == CAN_1)
    {
        CAN1_BIT_R |= config->bit_time.BRP | (config->bit_time.SJW <<6) | (config->bit_time.TSEG1 <<8) | (config->bit_time.TSEG2 <<12);
    }
}



/*********************************************************************************************************************
 * Description : Write Message data P.1053
 * Parameters  : can configuration , Message configuration , Data
 * Return      : None
 * *******************************************************************************************************************/

void Transmit_MESSAGE(CAN_Config *config , Message_Config *M_config , const uint8_t Data[])
{
    if(config->can_mode == CAN_0)
    {
        while(CAN0_IF1CRQ_R & 0x00008000);//wait while CAN0 Module is BUSY
        CAN0_IF1CMSK_R |= CAN_IF1CMSK_WRNRD |CAN_IF1CMSK_MASK | CAN_IF1CMSK_DATAA | CAN_IF1CMSK_DATAB | CAN_IF1CMSK_CONTROL | CAN_IF1CMSK_ARB ;
        CAN0_IF1CMSK_R &= ~CAN_IF2CMSK_NEWDAT;
        if(M_config->id_bits == Std)                             /* standard identifier */
        {
            /* register and configure ID[12:2] in the CANIFnARB2 register for bits [10:0] of the message identifier*/
            CAN0_IF1MSK2_R |= (M_config->id_accept & 0x000007ff) <<2;
            CAN0_IF1ARB2_R |= ((M_config->id_message) & 0x000007ff) <<2;
            /*Clear the XTD bit to indicate a standard identifier; set the DIR bit to indicate transmit;
             *  and set the MSGVAL bit to indicate that the message object is valid.*/
            CAN0_IF1ARB2_R &= ~CAN_IF1ARB2_XTD ;
            CAN0_IF1ARB2_R |= CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_DIR;
        }
        else if(M_config->id_bits == Ext)                       /*extended identifier*/
        {
            CAN0_IF1MSK1_R |= (uint16_t)M_config->id_accept;
            CAN0_IF1MSK2_R |= (CAN_IF1MSK2_IDMSK_M & (M_config->id_accept) >> 16); /*using a 29-bit identifier, these bits are used for bits [28:16] of the ID*/
            CAN0_IF1MSK2_R |= CAN_IF1MSK2_MXTD | CAN_IF1MSK2_MDIR;
            CAN0_IF1ARB1_R |= (uint16_t)M_config->id_message;
            CAN0_IF1ARB2_R |= (CAN_IF1MSK2_IDMSK_M & (M_config->id_message) >> 16); /*using a 29-bit identifier, these bits are used for bits [28:16] of the ID*/
            /*Set the XTD bit to indicate an extended identifier; set the DIR bit to indicate transmit;
             *  and set the MSGVAL bit to indicate that the message object is valid.*/
            CAN0_IF1ARB2_R |= CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_DIR | CAN_IF1ARB2_XTD;
        }
        /*
         * UNMASK --> Use mask (MSK, MXTD, and MDIR bits in the CANIFnMSKn registers) for acceptance filtering. P.1092
         * RMTEN  --> At the reception of a remote frame, the TXRQST bit in the CANIFnMCTL register is set to be set on the reception of a matching
         *             remote frame allowing automatic transmission.
         * EOB    --> Single message object or last message object of a FIFO Buffer for a single message object.
         * */
        CAN0_IF1MCTL_R |= CAN_IF1MCTL_UMASK |CAN_IF1MCTL_RMTEN | CAN_IF1MCTL_EOB;
        CAN0_IF1MCTL_R |= CAN_IF1MCTL_DLC_M & (M_config->DLC);

        WRITE_Message_CAN0(M_config , Data);

        /* Program the number of the message object to be transmitted in the MNUM field in the */
        CAN0_IF1CRQ_R |= ( M_config->id_message_obj & CAN_IF1CRQ_MNUM_M);
        while(CAN0_IF1CRQ_R & 0x00008000); //Wait for BUSY bit to clear
        /*set the TXRQST bit in the CANIFnMCTL register. Once this bit is set, the message object is available to be transmitted,
         *  depending on priority and bus availability.*/
        CAN0_IF1CMSK_R |= CAN_IF1CMSK_TXRQST | CAN_IF1CMSK_NEWDAT;


    }
    else if(config->can_mode == CAN_1)
    {
        while(CAN1_IF1CRQ_R & 0x00008000);//wait while CAN0 Module is BUSY
        CAN1_IF1CMSK_R |= CAN_IF1CMSK_WRNRD |CAN_IF1CMSK_MASK | CAN_IF1CMSK_DATAA | CAN_IF1CMSK_DATAB | CAN_IF1CMSK_CONTROL | CAN_IF1CMSK_ARB ;
        if(M_config->id_bits == Std)                                  /* standard identifier */
        {
            /* register and configure ID[12:2] in the CANIFnARB2 register for bits [10:0] of the message identifier*/
            CAN1_IF1MSK2_R |= (M_config->id_accept & 0x000007ff) <<2;
            CAN1_IF1MSK2_R &= ~CAN_IF1MSK2_MXTD;
            CAN1_IF1ARB2_R |= (M_config->id_message & 0x000007ff) <<2;
            /*Clear the XTD bit to indicate a standard identifier; set the DIR bit to indicate transmit;
             *  and set the MSGVAL bit to indicate that the message object is valid.*/
            CAN1_IF1ARB2_R &= ~CAN_IF1ARB2_XTD;
            CAN1_IF1ARB2_R |= CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_DIR;
        }
        else if(M_config->id_bits == Ext)                           /*extended identifier*/
        {
            CAN1_IF1MSK1_R |= M_config->id_accept;
            CAN1_IF1MSK2_R |= (CAN_IF1MSK2_IDMSK_M & (M_config->id_accept) >> 16); /*using a 29-bit identifier, these bits are used for bits [28:16] of the ID*/
            CAN1_IF1MSK2_R |= CAN_IF1MSK2_MXTD;
            CAN1_IF1ARB1_R |= M_config->id_message;
            CAN1_IF1ARB2_R |= (CAN_IF1MSK2_IDMSK_M & (M_config->id_message) >> 16); /*using a 29-bit identifier, these bits are used for bits [28:16] of the ID*/
            /*Set the XTD bit to indicate an extended identifier; set the DIR bit to indicate transmit;
             *  and set the MSGVAL bit to indicate that the message object is valid.*/
            CAN1_IF1ARB2_R |= CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_DIR | CAN_IF1ARB2_XTD;
        }
        /*
         * UNMASK --> Use mask (MSK, MXTD, and MDIR bits in the CANIFnMSKn registers) for acceptance filtering. P.1092
         * RMTEN  --> At the reception of a remote frame, the TXRQST bit in the CANIFnMCTL register is set to be set on the reception of a matching
         *             remote frame allowing automatic transmission.
         * EOB    --> Single message object or last message object of a FIFO Buffer for a single message object.
         * */
        CAN1_IF1MCTL_R |= CAN_IF1MCTL_UMASK | CAN_IF1MCTL_RMTEN | CAN_IF1MCTL_EOB;
        CAN1_IF1MCTL_R |= CAN_IF1MCTL_DLC_M & (M_config->DLC);
        CAN1_IF1CRQ_R |= ( M_config->id_message_obj & CAN_IF1CRQ_MNUM_M);
        /* Program the number of the message object to be transmitted in the MNUM field in the */

        WRITE_Message_CAN1(M_config , Data);

        /*set the TXRQST bit in the CANIFnMCTL register. Once this bit is set, the message object is available to be transmitted,
         *  depending on priority and bus availability.*/
        while(CAN1_IF1CRQ_R & 0x00008000); //Wait for BUSY bit to clear
        CAN1_IF1CMSK_R |= CAN_IF1CMSK_TXRQST| CAN_IF1CMSK_NEWDAT;
    }
}

/*********************************************************************************************************************
 * Description : Write Message data by can0
 * Parameters  : Message configuration , Data
 * Return      : None
 * *******************************************************************************************************************/

void WRITE_Message_CAN0(Message_Config *M_config , const uint8_t Data[])
{
    if(M_config->DLC == 0x0)
    {
        /* NO Data Frame */
    }
    else if(M_config->DLC == 0x1)
    {
        CAN0_IF1DA1_R |= Data[0];
    }
    else if(M_config->DLC == 0x2)
    {
        CAN0_IF1DA1_R |= Data[0];
        CAN0_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
    }
    else if(M_config->DLC == 0x3)
    {
        CAN0_IF1DA1_R |= Data[0];
        CAN0_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN0_IF1DA2_R |= Data[2];
    }
    else if(M_config->DLC == 0x4)
    {
        CAN0_IF1DA1_R |= Data[0];
        CAN0_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN0_IF1DA2_R |= Data[2];
        CAN0_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
    }
    else if(M_config->DLC == 0x5)
    {
        CAN0_IF1DA1_R |= Data[0];
        CAN0_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN0_IF1DA2_R |= Data[2];
        CAN0_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
        CAN0_IF1DB1_R |= Data[4];
    }
    else if(M_config->DLC == 0x6)
    {
        CAN0_IF1DA1_R |= Data[0];
        CAN0_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN0_IF1DA2_R |= Data[2];
        CAN0_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
        CAN0_IF1DB1_R |= Data[4];
        CAN0_IF1DB1_R |= (0x0000 | Data[5]) << 8 ;
    }
    else if(M_config->DLC == 0x7)
    {
        CAN0_IF1DA1_R |= Data[0];
        CAN0_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN0_IF1DA2_R |= Data[2];
        CAN0_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
        CAN0_IF1DB1_R |= Data[4];
        CAN0_IF1DB1_R |= (0x0000 | Data[5]) << 8 ;
        CAN0_IF1DB2_R |= Data[6];
    }
    else if(M_config->DLC == 0x8)
    {
        CAN0_IF1DA1_R |= Data[0];
        CAN0_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN0_IF1DA2_R |= Data[2];
        CAN0_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
        CAN0_IF1DB1_R |= Data[4];
        CAN0_IF1DB1_R |= (0x0000 | Data[5]) << 8 ;
        CAN0_IF1DB2_R |= Data[6];
        CAN0_IF1DB2_R |= (0x0000 | Data[5]) << 8 ;
    }
    else
    {
        CAN0_IF1DA1_R |= Data[0];
        CAN0_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN0_IF1DA2_R |= Data[2];
        CAN0_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
        CAN0_IF1DB1_R |= Data[4];
        CAN0_IF1DB1_R |= (0x0000 | Data[5]) << 8 ;
        CAN0_IF1DB2_R |= Data[6];
        CAN0_IF1DB2_R |= (0x0000 | Data[5]) << 8 ;
    }
}

/*********************************************************************************************************************
 * Description : Write Message data by can1
 * Parameters  : Message configuration , Data
 * Return      : None
 * *******************************************************************************************************************/

void WRITE_Message_CAN1(Message_Config *M_config , const uint8_t Data[])
{
    if(M_config->DLC == 0x0)
    {
        /* NO Data Frame */
    }
    else if(M_config->DLC == 0x1)
    {
        CAN1_IF1DA1_R |= Data[0];
    }
    else if(M_config->DLC == 0x2)
    {
        CAN1_IF1DA1_R |= Data[0];
        CAN1_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
    }
    else if(M_config->DLC == 0x3)
    {
        CAN1_IF1DA1_R |= Data[0];
        CAN1_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN1_IF1DA2_R |= Data[2];
    }
    else if(M_config->DLC == 0x4)
    {
        CAN1_IF1DA1_R |= Data[0];
        CAN1_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN1_IF1DA2_R |= Data[2];
        CAN1_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
    }
    else if(M_config->DLC == 0x5)
    {
        CAN1_IF1DA1_R |= Data[0];
        CAN1_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN1_IF1DA2_R |= Data[2];
        CAN1_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
        CAN1_IF1DB1_R |= Data[4];
    }
    else if(M_config->DLC == 0x6)
    {
        CAN1_IF1DA1_R |= Data[0];
        CAN1_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN1_IF1DA2_R |= Data[2];
        CAN1_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
        CAN1_IF1DB1_R |= Data[4];
        CAN1_IF1DB1_R |= (0x0000 | Data[5]) << 8 ;
    }
    else if(M_config->DLC == 0x7)
    {
        CAN1_IF1DA1_R |= Data[0];
        CAN1_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN1_IF1DA2_R |= Data[2];
        CAN1_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
        CAN1_IF1DB1_R |= Data[4];
        CAN1_IF1DB1_R |= (0x0000 | Data[5]) << 8 ;
        CAN1_IF1DB2_R |= Data[6];
    }
    else if(M_config->DLC == 0x8)
    {
        CAN1_IF1DA1_R |= Data[0];
        CAN1_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN1_IF1DA2_R |= Data[2];
        CAN1_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
        CAN1_IF1DB1_R |= Data[4];
        CAN1_IF1DB1_R |= (0x0000 | Data[5]) << 8 ;
        CAN1_IF1DB2_R |= Data[6];
        CAN1_IF1DB2_R |= (0x0000 | Data[5]) << 8 ;
    }
}


/*********************************************************************************************************************
 * Description : Update message data
 * Parameters  : Can configuration , Message configuration , Data
 * Return      : None
 * *******************************************************************************************************************/

void Update_Message(CAN_Config *config , Message_Config *M_config , const uint8_t Data[])
{
    if(config->can_mode == CAN_0)
    {
        /*In order to only update the data in a message object, the WRNRD,
         * DATAA and DATAB bits in the CANIFnMSKn register are set,*/
        CAN0_IF1CMSK_R |= CAN_IF1CMSK_WRNRD |CAN_IF1CMSK_MASK | CAN_IF1CMSK_DATAA | CAN_IF1CMSK_DATAB;
        CAN0_IF1DA1_R |= Data[0];
        CAN0_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN0_IF1DA2_R |= Data[2];
        CAN0_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
        CAN0_IF1DB1_R |= Data[4];
        CAN0_IF1DB1_R |= (0x0000 | Data[5]) << 8 ;
        CAN0_IF1DB2_R |= Data[6];
        CAN0_IF1DB2_R |= (0x0000 | Data[5]) << 8 ;

        /*the number of the message object is written to the MNUM field in the CAN IFn Command Request (CANIFnCRQ) register.
         *  To begin transmission of the new data as soon as possible, set the TXRQST bit in the CANIFnMSKn register P.1054*/

        CAN0_IF1CRQ_R |= ( M_config->id_message_obj & CAN_IF1CRQ_MNUM_M);
        CAN0_IF1MCTL_R |= CAN_IF1MCTL_TXRQST | CAN_IF1CMSK_NEWDAT;
    }
    else if(config->can_mode == CAN_1)
    {
        /*In order to only update the data in a message object, the WRNRD,
         * DATAA and DATAB bits in the CANIFnMSKn register are set,*/
        CAN1_IF1CMSK_R |= CAN_IF1CMSK_WRNRD |CAN_IF1CMSK_MASK | CAN_IF1CMSK_DATAA | CAN_IF1CMSK_DATAB;
        CAN1_IF1DA1_R |= Data[0];
        CAN1_IF1DA1_R |= (0x0000 | Data[1]) << 8 ;
        CAN1_IF1DA2_R |= Data[2];
        CAN1_IF1DA2_R |= (0x0000 | Data[3]) << 8 ;
        CAN1_IF1DB1_R |= Data[4];
        CAN1_IF1DB1_R |= (0x0000 | Data[5]) << 8 ;
        CAN1_IF1DB2_R |= Data[6];
        CAN1_IF1DB2_R |= (0x0000 | Data[5]) << 8 ;

        /*the number of the message object is written to the MNUM field in the CAN IFn Command Request (CANIFnCRQ) register.
         *  To begin transmission of the new data as soon as possible, set the TXRQST bit in the CANIFnMSKn register P.1054*/

        CAN1_IF1CRQ_R |= ( M_config->id_message_obj & CAN_IF1CRQ_MNUM_M);
        CAN1_IF1MCTL_R |= CAN_IF1MCTL_TXRQST | CAN_IF1CMSK_NEWDAT;
    }
}

/*********************************************************************************************************************
 * Description : The message handler stores the message from the CAN controller receive shift register into the
 *                matching message object in the message RAM P.1055 , P.1056.
 * Parameters  : can configuration , Message configuration , Data
 * Return      : None
 * *******************************************************************************************************************/

void RECEIVE_MESSAGE(CAN_Config *config , Message_Config *M_config)
{
    if(config->can_mode == CAN_0)
    {
        while(CAN0_IF2CRQ_R & 0x00008000);//wait while CAN0 Module is BUSY
        /*he WRNRD bit is set to specify a write to the message RAM*/
        CAN0_IF2CMSK_R &= ~CAN_IF2CMSK_WRNRD;
        CAN0_IF2CMSK_R |= CAN_IF2CMSK_MASK | CAN_IF2CMSK_DATAA | CAN_IF2CMSK_DATAB | CAN_IF2CMSK_CONTROL | CAN_IF2CMSK_ARB ;
        if(M_config->id_bits == Std)
        {
            /* register and configure ID[12:2] in the CANIFnARB2 register for bits [10:0] of the message identifier*/
            CAN0_IF2MSK2_R |= (M_config->id_accept & 0x000007ff) <<2;
            CAN0_IF2MSK2_R &= ~CAN_IF2MSK2_MXTD;
            CAN0_IF2ARB2_R |= (M_config->id_message & 0x000007ff) <<2;
            /*set the MSGVAL bit to indicate a valid message; and clear the DIR bit to specify receive.*/
            CAN0_IF2ARB2_R &= ~ CAN_IF2ARB2_DIR;
            CAN0_IF2ARB2_R |= CAN_IF2ARB2_MSGVAL | CAN_IF2ARB2_XTD ;
        }
        else if(M_config->id_bits == Ext)
        {
            CAN0_IF2MSK1_R |= M_config->id_accept;
            CAN0_IF2MSK2_R |= (CAN_IF2MSK2_IDMSK_M & (M_config->id_accept) >> 16); /*using a 29-bit identifier, these bits are used for bits [28:16] of the ID*/
            CAN0_IF2MSK2_R |= CAN_IF2MSK2_MXTD;
            CAN0_IF2ARB1_R |= M_config->id_message;
            CAN0_IF2ARB2_R |= (CAN_IF2MSK2_IDMSK_M & (M_config->id_message) >> 16); /*using a 29-bit identifier, these bits are used for bits [28:16] of the ID*/
            /*set the MSGVAL bit to indicate a valid message; and clear the DIR bit to specify receive.*/
            CAN0_IF2ARB2_R |= CAN_IF2ARB2_MSGVAL | CAN_IF2ARB2_XTD;
            CAN0_IF2ARB2_R &= ~CAN_IF2ARB2_DIR;
        }
        /*
         * UNMASK --> Use mask (MSK, MXTD, and MDIR bits in the CANIFnMSKn registers) for acceptance filtering. P.1092
         * RMTEN  --> At the reception of a remote frame, the TXRQST bit in the CANIFnMCTL register is set.
         * EOB    --> Single message object or last message object of a FIFO Buffer.
         * The NEWDAT bit of the CANIFnMCTL register is set to indicate that new data has been received
         * */
        CAN0_IF2MCTL_R |= CAN_IF2MCTL_UMASK | CAN_IF2MCTL_EOB | CAN_IF2CMSK_NEWDAT;
        CAN0_IF2MCTL_R &= ~CAN_IF2MCTL_RMTEN ;
        CAN0_IF2MCTL_R &= ~CAN_IF2MCTL_TXRQST;  /*The TXRQST bit of this message object should be cleared to prevent the transmission of a remote frame.*/
       /*Configure the DLC[3:0] field to specify the size of the data frame*/
        CAN0_IF2MCTL_R |= CAN_IF2MCTL_DLC_M & (M_config->DLC);
        CAN0_IF2CRQ_R  |= ( M_config->id_message_obj & CAN_IF2CRQ_MNUM_M);
        CAN0_IF2CMSK_R |= CAN_IF2CMSK_NEWDAT;

        READ_Message_CAN0(M_config);

        while(CAN0_IF2CRQ_R & 0x00008000);//wait while CAN0 Module is BUSY
    }
    else if(config->can_mode == CAN_1)
    {
        while(CAN1_IF2CRQ_R & 0x00008000);//wait while CAN0 Module is BUSY
        CAN1_IF2CMSK_R &= ~CAN_IF1CMSK_WRNRD;
        CAN1_IF2CMSK_R |= CAN_IF2CMSK_MASK | CAN_IF2CMSK_DATAA | CAN_IF2CMSK_DATAB | CAN_IF2CMSK_CONTROL | CAN_IF2CMSK_ARB ;
        if(M_config->id_bits == Std)
        {
            CAN1_IF2MSK2_R |= (M_config->id_accept & 0x000007ff) <<2;
            CAN1_IF2MSK2_R &= ~CAN_IF2MSK2_MXTD;
            CAN1_IF2ARB2_R |= (M_config->id_message & 0x000007ff) <<2;
            CAN1_IF2ARB2_R &= ~ CAN_IF2ARB2_DIR;
            CAN1_IF2ARB2_R |= CAN_IF2ARB2_MSGVAL | CAN_IF2ARB2_XTD ;
        }
        else if(M_config->id_bits == Ext)
        {
            CAN1_IF2MSK1_R |= M_config->id_accept;
            CAN1_IF2MSK2_R |= (CAN_IF2MSK2_IDMSK_M & (M_config->id_accept) >> 16); /*using a 29-bit identifier, these bits are used for bits [28:16] of the ID*/
            CAN1_IF2MSK2_R |= CAN_IF2MSK2_MXTD;
            CAN1_IF2ARB1_R |= M_config->id_message;
            CAN1_IF2ARB2_R |= (CAN_IF2MSK2_IDMSK_M & (M_config->id_message) >> 16); /*using a 29-bit identifier, these bits are used for bits [28:16] of the ID*/
            CAN1_IF2ARB2_R &= ~ CAN_IF2ARB2_DIR;
            CAN1_IF2ARB2_R |= CAN_IF2ARB2_MSGVAL | CAN_IF2ARB2_XTD ;
        }
        /*
         * UNMASK --> Use mask (MSK, MXTD, and MDIR bits in the CANIFnMSKn registers) for acceptance filtering. P.1092
         * RMTEN  --> At the reception of a remote frame, the TXRQST bit in the CANIFnMCTL register is set.
         * EOB    --> Single message object or last message object of a FIFO Buffer.
         * The NEWDAT bit of the CANIFnMCTL register is set to indicate that new data has been received
         * */
        CAN1_IF2MCTL_R |=  CAN_IF2MCTL_UMASK | CAN_IF2MCTL_EOB | CAN_IF2CMSK_NEWDAT;
        CAN1_IF2MCTL_R &= ~CAN_IF2MCTL_RMTEN ;
        CAN1_IF2MCTL_R &= ~CAN_IF2MCTL_TXRQST;  /*The TXRQST bit of this message object should be cleared to prevent the transmission of a remote frame.*/
        CAN1_IF2MCTL_R |=  CAN_IF2MCTL_DLC_M & (M_config->DLC);

        CAN1_IF2CRQ_R |= ( M_config->id_message_obj & CAN_IF2CRQ_MNUM_M);
        CAN0_IF2CMSK_R |= CAN_IF2CMSK_NEWDAT;

        READ_Message_CAN1(M_config);

        while(CAN1_IF2CRQ_R & 0x00008000);//wait while CAN0 Module is BUSY
    }
}


/*********************************************************************************************************************
 * Description : Read Message data by can0
 * Parameters  : Message configuration , Data
 * Return      : None
 * *******************************************************************************************************************/

void READ_Message_CAN0(Message_Config *M_config)
{
    char data[8];
    if(M_config->DLC == 0x0)
    {
        /* NO Data Frame */
    }
    else if(M_config->DLC == 0x1)
    {
        data[0] = (0x00FF & CAN0_IF2DA1_R);
    }
    else if(M_config->DLC == 0x2)
    {

        data[0] = (0x00FF & CAN0_IF2DA1_R);
        data[1] = ((0xFF00 & CAN0_IF2DA1_R)>>8);
    }
    else if(M_config->DLC == 0x3)
    {
        data[0] = (0x00FF & CAN0_IF2DA1_R);
        data[1] = ((0xFF00 & CAN0_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN0_IF2DA2_R);
    }
    else if(M_config->DLC == 0x4)
    {
        data[0] = (0x00FF & CAN0_IF2DA1_R);
        data[1] = ((0xFF00 & CAN0_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN0_IF2DA2_R);
        data[3] = ((0xFF00 & CAN0_IF2DA2_R)>>8);
    }
    else if(M_config->DLC == 0x5)
    {
        data[0] = (0x00FF & CAN0_IF2DA1_R);
        data[1] = ((0xFF00 & CAN0_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN0_IF2DA2_R);
        data[3] = ((0xFF00 & CAN0_IF2DA2_R)>>8);
        data[4] = (0x00FF & CAN0_IF2DB1_R);
    }
    else if(M_config->DLC == 0x6)
    {
        data[0] = (0x00FF & CAN0_IF2DA1_R);
        data[1] = ((0xFF00 & CAN0_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN0_IF2DA2_R);
        data[3] = ((0xFF00 & CAN0_IF2DA2_R)>>8);
        data[4] = (0x00FF & CAN0_IF2DB1_R);
        data[5] = ((0xFF00 & CAN0_IF2DB1_R)>>8);
    }
    else if(M_config->DLC == 0x7)
    {
        data[0] = (0x00FF & CAN0_IF2DA1_R);
        data[1] = ((0xFF00 & CAN0_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN0_IF2DA2_R);
        data[3] = ((0xFF00 & CAN0_IF2DA2_R)>>8);
        data[4] = (0x00FF & CAN0_IF2DB1_R);
        data[5] = ((0xFF00 & CAN0_IF2DB1_R)>>8);
        data[6] = (0x00FF & CAN0_IF2DB2_R);
    }
    else if(M_config->DLC == 0x8)
    {
        data[0] = (0x00FF & CAN0_IF2DA1_R);
        data[1] = ((0xFF00 & CAN0_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN0_IF2DA2_R);
        data[3] = ((0xFF00 & CAN0_IF2DA2_R)>>8);
        data[4] = (0x00FF & CAN0_IF2DB1_R);
        data[5] = ((0xFF00 & CAN0_IF2DB1_R)>>8);
        data[6] = (0x00FF & CAN0_IF2DB2_R);
        data[7] = ((0xFF00 & CAN0_IF2DB2_R)>>8);
    }
    else
    {
        data[0] = (0x00FF & CAN0_IF2DA1_R);
        data[1] = ((0xFF00 & CAN0_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN0_IF2DA2_R);
        data[3] = ((0xFF00 & CAN0_IF2DA2_R)>>8);
        data[4] = (0x00FF & CAN0_IF2DB1_R);
        data[5] = ((0xFF00 & CAN0_IF2DB1_R)>>8);
        data[6] = (0x00FF & CAN0_IF2DB2_R);
        data[7] = ((0xFF00 & CAN0_IF2DB2_R)>>8);
    }
}

/*********************************************************************************************************************
 * Description : Read Message data by can1
 * Parameters  : Message configuration , Data
 * Return      : None
 * *******************************************************************************************************************/

void READ_Message_CAN1(Message_Config *M_config)
{
    char data[8];
    if(M_config->DLC == 0x0)
    {
        /* NO Data Frame */
    }
    else if(M_config->DLC == 0x1)
    {
        data[0] = (0x00FF & CAN1_IF2DA1_R);
    }
    else if(M_config->DLC == 0x2)
    {

        data[0] = (0x00FF & CAN1_IF2DA1_R);
        data[1] = ((0xFF00 & CAN1_IF2DA1_R)>>8);
    }
    else if(M_config->DLC == 0x3)
    {
        data[0] = (0x00FF & CAN1_IF2DA1_R);
        data[1] = ((0xFF00 & CAN1_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN1_IF2DA2_R);
    }
    else if(M_config->DLC == 0x4)
    {
        data[0] = (0x00FF & CAN1_IF2DA1_R);
        data[1] = ((0xFF00 & CAN1_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN1_IF2DA2_R);
        data[3] = ((0xFF00 & CAN1_IF2DA2_R)>>8);
    }
    else if(M_config->DLC == 0x5)
    {
        data[0] = (0x00FF & CAN1_IF2DA1_R);
        data[1] = ((0xFF00 & CAN1_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN1_IF2DA2_R);
        data[3] = ((0xFF00 & CAN1_IF2DA2_R)>>8);
        data[4] = (0x00FF & CAN1_IF2DB1_R);
    }
    else if(M_config->DLC == 0x6)
    {
        data[0] = (0x00FF & CAN1_IF2DA1_R);
        data[1] = ((0xFF00 & CAN1_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN1_IF2DA2_R);
        data[3] = ((0xFF00 & CAN1_IF2DA2_R)>>8);
        data[4] = (0x00FF & CAN1_IF2DB1_R);
        data[5] = ((0xFF00 & CAN1_IF2DB1_R)>>8);
    }
    else if(M_config->DLC == 0x7)
    {
        data[0] = (0x00FF & CAN1_IF2DA1_R);
        data[1] = ((0xFF00 & CAN1_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN1_IF2DA2_R);
        data[3] = ((0xFF00 & CAN1_IF2DA2_R)>>8);
        data[4] = (0x00FF & CAN1_IF2DB1_R);
        data[5] = ((0xFF00 & CAN1_IF2DB1_R)>>8);
        data[6] = (0x00FF & CAN1_IF2DB2_R);
    }
    else if(M_config->DLC == 0x8)
    {
        data[0] = (0x00FF & CAN1_IF2DA1_R);
        data[1] = ((0xFF00 & CAN1_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN1_IF2DA2_R);
        data[3] = ((0xFF00 & CAN1_IF2DA2_R)>>8);
        data[4] = (0x00FF & CAN1_IF2DB1_R);
        data[5] = ((0xFF00 & CAN1_IF2DB1_R)>>8);
        data[6] = (0x00FF & CAN1_IF2DB2_R);
        data[7] = ((0xFF00 & CAN1_IF2DB2_R)>>8);
    }
    else
    {
        data[0] = (0x00FF & CAN1_IF2DA1_R);
        data[1] = ((0xFF00 & CAN1_IF2DA1_R)>>8);
        data[2] = (0x00FF & CAN1_IF2DA2_R);
        data[3] = ((0xFF00 & CAN1_IF2DA2_R)>>8);
        data[4] = (0x00FF & CAN1_IF2DB1_R);
        data[5] = ((0xFF00 & CAN1_IF2DB1_R)>>8);
        data[6] = (0x00FF & CAN1_IF2DB2_R);
        data[7] = ((0xFF00 & CAN1_IF2DB2_R)>>8);
    }
}


/*********************************************************************************************************************
 * Description : Enable can
 * Parameters  : Can configuration
 * Return      : None
 * *******************************************************************************************************************/

void CAN_Enable(CAN_Config *config)
{
    CAN1_CTL_R |= CAN_CTL_INIT;
}

/*********************************************************************************************************************
 * Description : Disable can
 * Parameters  : Can configuration
 * Return      : None
 * *******************************************************************************************************************/

void CAN_Disable(CAN_Config *config)
{
    CAN1_CTL_R &= ~CAN_CTL_INIT;
}



