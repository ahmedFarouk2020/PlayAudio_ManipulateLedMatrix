#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/DIO_REG.h"
#include "../include/DIO.h"
#include "../include/DIO_Cfg.h"


#define NUM_OF_PORTS ((u8)3)


GPIO_TypeDef * Ports[NUM_OF_PORTS] = { 
	(GPIO_TypeDef*)GPIOA_BASE_ADDRESS,
 	(GPIO_TypeDef*)GPIOB_BASE_ADDRESS,
	(GPIO_TypeDef*)GPIOC_BASE_ADDRESS
};

void DIO_Init(void)
 {
	u8 Loop;

	for(Loop = (u8)0; Loop < DIO_NUM_OF_CHANNELS; Loop++)
	{
		u8 PortId;
		/*read the port Id from link time configuration*/
		PortId = DIO_ConfigParam[Loop].PortId;

		/*verify Port Id*/
		if(PortId < NUM_OF_PORTS)
		{
			/*Enable clock from RCC driver */
        	GPIO_TypeDef * GPIOx =Ports[PortId];

            u8 PinNumber = DIO_ConfigParam[Loop].PinNum;
			u8 PinDir = DIO_ConfigParam[Loop].PortDirection;

			if (PinDir == 0) /* Input */
			{
				if (PinNumber < 8)
				{
					/* Clear the 4-bit segment before write */
					GPIOx->CRL &= ~( (0x0F)<< (4*PinNumber) );

					GPIOx->CRL |= (PinDir&0x03)<<(4*PinNumber) | 
					(DIO_ConfigParam[Loop].PuPd&0x03)<<(4*PinNumber+2);
				} else {
					/* Clear the 4-bit segment before write */
					GPIOx->CRH &= ~( (0x0F)<< (4*(PinNumber-8)) );

					GPIOx->CRH |= (PinDir&0x03)<<(4*(PinNumber-8)) | 
					(DIO_ConfigParam[Loop].PuPd&0x03)<<(4*(PinNumber-8)+2);
				} 
			} else { /* Output */
				if (PinNumber < 8)
				{
					/* Clear the 4-bit segment before write */
					GPIOx->CRL &= ~( (0x0F)<< (4*PinNumber) );

					GPIOx->CRL |= (PinDir&0x03)<<(4*PinNumber) | 
						(PinDir&0b00000100)<<(4*PinNumber+3) | /* CNF1 */
						(DIO_ConfigParam[Loop].OutputType&0x01)<<(4*PinNumber+2);/*CNF0*/
				} else {
					/* Clear the 4-bit segment before write */
					GPIOx->CRH &= ~( (0x0F)<< (4*(PinNumber-8)) );

					GPIOx->CRH |= (PinDir&0x03)<<(4*(PinNumber-8)) | 
						(PinDir&0b00000100)<<(4*(PinNumber-8)+3) | /* CNF1 */
						(DIO_ConfigParam[Loop].OutputType&0x01)<<(4*(PinNumber-8)+2);/*CNF0*/
				}
			}
		} else {
			/* Invalid port */
		}
	}
}

/*Function shall do the following:
1- To Validate Channel ID
2- To get the port ID from configuration based on the Channel ID
3- To write port for the masked pins with the passed data value
4- Data shall be written only for the output pins*/
void DIO_ChannelWrite(u8 ChannelId, u8 Data)
{

	if (ChannelId<DIO_NUM_OF_CHANNELS)
	{
		u8 PortId = DIO_ConfigParam[ChannelId].PortId;
		if(DIO_ConfigParam[ChannelId].PortDirection > 0)
		{
			GPIO_TypeDef * GPIOx =Ports[PortId];
			if(Data != 0)
			{
			    GPIOx->ODR |= (1<< (DIO_ConfigParam[ChannelId].PinNum));
			}
			else
			{
			    GPIOx->ODR &= ~(1<< (DIO_ConfigParam[ChannelId].PinNum));
			}
		}
		else // INPUT -> do nothing
		{}

	}
}

/*
 * LSB in Data affect channel 0 in channel group
 */
void DIO_ChannelGroupWrite(u8 channelGroup_id, u16 data)
{
    if(channelGroup_id < DIO_NUM_OF_CHANNELGROUPS){

        u8 it;
        u8 channel_data = (u8)0;

        for(it = (u8)0; it < DIO_ChannelGroupList[channelGroup_id].channelGroup_size; it++)
        {
            channel_data = data & (u8)1;
            DIO_ChannelWrite(DIO_ChannelGroupList[channelGroup_id].channelsId[it], channel_data);
            data = data>> (u8)1;
        }
    }
}


void DIO_ChannelGroupRead(u8 channelGroup_id, unsigned short int* DataPtr)
{
    *DataPtr = 0; /* reinit the buffer */

    if(channelGroup_id <= DIO_NUM_OF_CHANNELGROUPS)
    {
        u8 it ;
        unsigned short int channel_data = (unsigned short int)0;

        for(it = (u8)0; it < DIO_ChannelGroupList[channelGroup_id].channelGroup_size; ++it)
        {
            DIO_ChannelRead(DIO_ChannelGroupList[channelGroup_id].channelsId[it], &channel_data);
            *DataPtr |= ( (channel_data&1) <<it );
        }
    }
}

/*Function shall do the following:
1- To Validate Channel ID
2- To get the port ID from configuration based on the Channel ID
3- To read port for the masked pins and other pins shall be returned by 0
4- Data shall be read only for the input pins*/

void DIO_ChannelRead(u8 ChannelId, unsigned short int *DataPtr)
{
	if (ChannelId<DIO_NUM_OF_CHANNELS)
		{
			u8 PortId;
			PortId = DIO_ConfigParam[ChannelId].PortId;
            GPIO_TypeDef * GPIOx =Ports[PortId];

			if(DIO_ConfigParam[ChannelId].PortDirection == 0) /* input */
			{
				*DataPtr = ( (1<<(DIO_ConfigParam[ChannelId].PinNum)) & GPIOx->IDR)?1:0;
			}

		}

}
