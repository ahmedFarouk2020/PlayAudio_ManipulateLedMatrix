/*
 * DIO_Cfg.h
 *
 *  Created on: Mar 23, 2022
 *      Author: Farouk
 */


#ifndef INC_DIO_CFG_H_
#define INC_DIO_CFG_H_

#define DIO_NUM_OF_CHANNELS               ((u8)25)
#define DIO_NUM_OF_CHANNELGROUPS          ((u8)3)
#define DIO_MAX_NUM_OF_CHANNELS_IN_GROUP  ((u8)8)

typedef struct
{
    u8 PortId;
    u8 PinNum;
    /* first 2 bits(from LSB) are MODE then 3rd bit is AF or OUT */
    u8 PortDirection;/* 0=input,1=output10M, 2=output2M,3=output50M, 5=AF10, 6=AF2, 7=AF50 */
    u8 PuPd; /* 1 = No-pull-up-pull-down, 2 up, 2 down, 0 analog */
    u8 OutputType;/*0 = push-pull,1 = open drain*/

}DIO_ChannelConfigType;


typedef struct
{
    u8 channelsId[DIO_MAX_NUM_OF_CHANNELS_IN_GROUP];
    u8 channelGroup_size;
}DIO_ChannelGroupConfigType;



extern const DIO_ChannelConfigType DIO_ConfigParam[DIO_NUM_OF_CHANNELS];
extern const DIO_ChannelGroupConfigType DIO_ChannelGroupList[DIO_NUM_OF_CHANNELGROUPS];

#endif /* INC_DIO_CFG_H_ */
