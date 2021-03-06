/********************************************************************************
 * File Name: can.h
 *
 * Author: Basmala Magdy
 *
 * Created on: Sep 5, 2021
 *
 * Description: CAN driver
 *******************************************************************************/

#ifndef CAN_H_
#define CAN_H_
// **************************** mode ********************************
#define RCGC0_CLOCK_MODE       (*((volatile unsigned long*)0x400FE100))
#define RCGC2_CLOCK_PORT       (*((volatile unsigned long*)0x400FE108))


/**************************  Register /map ***********************************/
#define CAN0  (unsigned long)(0x40040000)
#define CAN1  (unsigned long)(0x40041000)

//********************** REG ************************

#define GPIOA 0
#define GPIOB 1
#define GPIOE 4
#define GPIOF 5

#define can0 24
#define can1 25


/*******************************************************************************
 *                      MODULE DATA TYPES                                      *
 *******************************************************************************/

typedef enum
{
     CAN_0 , CAN_1
}CAN_MODE_Config;

/********************************************************************************************************************/
 /********************************************************************************************************************/
 /*************************              CANBIT Register Field Setting   p.1063                                    *************************/
 /*************************              ------------------------------------
  *                                      Example for Bit Timing at High Baud Rate                                  **************************/
 /*************************              TSEG2      --> Phase2 - 1         --> TSeg2 -1 = 1-1               = 0    **************************/
 /*************************              TSEG1      --> Prop + Phase1 - 1  --> TSeg1 -1 = 3-1                =2    **************************/
 /*************************              SJW        --> SJW - 1            --> SJW -1 = 1-1                  = 0   **************************/
/*************************              BRP        --> BRP -1             --> = Baud rate prescaler - 1= 5-1=4     **************************/
/*************************              ------------------------------------
 *                                       Example for Bit Timing at Low Baud Rate                                   *************************/
/*************************              TSEG2      --> Phase2 - 1         --> TSeg2 -1 = 4-1               = 3   *************************/
/*************************              TSEG1      --> Prop + Phase1 - 1  --> TSeg1 -1 = 5-1                =4    *************************/
/*************************              SJW        --> SJW - 1            --> SJW -1 = 4-1                  = 0   *************************/
/*************************              BRP        --> BRP -1             --> = Baud rate prescaler - 1= 50-1=49     *************************/
 /********************************************************************************************************************/
 /********************************************************************************************************************/
typedef struct
{
    uint8_t TSEG2;
    uint8_t TSEG1;
    uint8_t SJW;
    uint8_t BRP;
}BIT_TIME_Config;

/********** PORT configuration *****************/
typedef enum
{
    A,B,E,F
}CAN_PORT_Config;

typedef struct
{
    CAN_MODE_Config can_mode;
    BIT_TIME_Config bit_time;
    CAN_PORT_Config can_port;
}CAN_Config;

/**************************************************************/
typedef enum
{
    Std, Ext
}Message_ID;
typedef struct
{
    uint8_t id_accept;
    uint8_t id_message;
    uint8_t id_message_obj;
    uint8_t DLC;
    Message_ID id_bits;

}Message_Config;

/**************************************************************************************************************************/
/**************************************************************************************************************************/
/*                                               CAN fUNCTIONS PROTOTYPES                                                 */
/**************************************************************************************************************************/
/**************************************************************************************************************************/

void CANX_INIT(CAN_Config *config);
void CANx_PIN_INIT(CAN_Config *config);
void CANx_TIME_BIT(CAN_Config *config);
void Transmit_MESSAGE(CAN_Config *config , Message_Config *M_config , const uint8_t Data[]);
void WRITE_Message_CAN0(Message_Config *M_config , const uint8_t Data[]);
void WRITE_Message_CAN1(Message_Config *M_config , const uint8_t Data[]);
void Update_Message(CAN_Config *config , Message_Config *M_config , const uint8_t Data[]);
void RECEIVE_MESSAGE(CAN_Config *config , Message_Config *M_config);
void READ_Message_CAN0(Message_Config *M_config);
void READ_Message_CAN1(Message_Config *M_config);


#endif /* CAN_H_ */
