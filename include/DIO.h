/*
 * DIO.h
 *
 *  Created on: Mar 23, 2022
 *      Author: moham
 */

#ifndef INC_DIO_H_
#define INC_DIO_H_

void DIO_Init(void);
void DIO_ChannelWrite(u8 ChannelId, u8 Data);
void DIO_ChannelRead(u8 ChannelId, u16 *DataPtr);
void DIO_ChannelGroupWrite(u8 channelGroup_id, u16 data);
void DIO_ChannelGroupRead(u8 channelGroup_id, u16* DataPtr);
#endif /* INC_DIO_H_ */
