#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO.h"
#include "STK_interface.h"

#include "DAC_interface.h"
#include "DAC_private.h"
#include "DAC_config.h"


static volatile u8 time = 125;// 1/freq

void DAC_voidReadAudioArrSync(const u8 *audio_array, u16 ArraySize)
{
	for(u16 i=0 ; i<ArraySize ; i++)
	{
		DIO_ChannelGroupWrite(DAC_DIO_CHANNELGROUP,audio_array[i]);
		DAC_delay();
	}
}


void DAC_voidReadAudioArrAsync(u8 *audio_array, u16 ArraySize)
{
	static volatile u16 counter = 0;
	DIO_ChannelGroupWrite(DAC_DIO_CHANNELGROUP,audio_array[counter]);
	counter = (counter + 1) % ArraySize;
}



void  DAC_voidIncreaseFreq(void)
{
	if(time > 15)
	   time -= 10  ;
}

void  DAC_voidDecreaseFreq(void)
{
	if(time < 230)
	   time += 10  ;
}

void DAC_delay(void)
{
	for(u8 i=0 ; i<time ;i++)
	{
		asm("NOP");
	}
}
