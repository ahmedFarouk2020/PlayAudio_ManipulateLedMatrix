
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO.h"
#include "STK_interface.h"

#include "LEDMRX_interface.h"
#include "LEDMRX_private.h"
#include "LEDMRX_config.h"

static volatile u8 	HLEDMRX_u8Speed;
static volatile u8 HLEDMRX_u8EnableShift;
static volatile u8 staticImage;

void _2ms_delay(void)// for LEDMTRX (2ms)
{
	for(u8 i=0 ; i<45 ;i++)
	{
		for(u8 j=0 ; j<45 ;j++)
		{
			asm("NOP");
		}
	}
}

void HLEDMRX_voidInit(void)
{
	HLEDMRX_u8Speed = 20;
	HLEDMRX_u8EnableShift = 1;
	staticImage = 0;
}

static void HLEDMRX_voidDisableAllCols(void)
{
	/* disable all colmns */
	DIO_ChannelGroupWrite(COL_GROUP,0xffff);
}

static void HLEDMRX_voidSetCol(u8 copy_u8Data)
{
	DIO_ChannelGroupWrite(ROW_GROUP,copy_u8Data);
}

void HLEDMRX_voidDisplay(u8 *copy_u8Data)
{
	HLEDMRX_voidDisableAllCols();
	int i;
	for(i=0; i< NUM_OF_COLS; i++)
	{
		HLEDMRX_voidSetCol(copy_u8Data[i]);
		DIO_ChannelWrite(COL_START_INDEX+i, 0); // activate col

		_2ms_delay();
//		MSTK_voidSetBusyWait(2);

		DIO_ChannelWrite(COL_START_INDEX+i, 1); // deactivate col
	}
}


static void HLEDMRX_RShift(u8 *ptr, u8 SentenceWidth)
{
	s8 i;
	for(i=SentenceWidth-LEDMTRX_Width ; i>=0;i--)
	{
		int k = 0;
		while(k < HLEDMRX_u8Speed)
		{
			HLEDMRX_voidDisplay(&ptr[i]);
			k++;
		}
	}
}
static void HLEDMRX_LShift(u8 *ptr, u8 SentenceWidth)
{
	u8 i;
	for(i=0 ; i<=SentenceWidth-LEDMTRX_Width ;i++)
	{
		int k = 0;
		while(k < HLEDMRX_u8Speed)
		{
			HLEDMRX_voidDisplay(&ptr[i]);
			k++;
		}
	}
}
void HLEDMRX_voidShift(u8 *ptr, u8 SentenceWidth, u8 shift_direction)
{

	if(  (HLEDMRX_u8EnableShift==1) && (shift_direction == TO_LEFT)  )
	{
		HLEDMRX_LShift(ptr, SentenceWidth);
	}

	else if( (HLEDMRX_u8EnableShift==1) && (shift_direction == TO_RIGHT) )
	{
		HLEDMRX_RShift(ptr, SentenceWidth);
	}
	else   /* Shifting is disabled */
	{
		int k = 0;
		while(k < HLEDMRX_u8Speed)
		{
			HLEDMRX_voidDisplay(&ptr[0]);
			k++;
		}
	}

}


void HLEDMRX_voidShowStatic(u8 *ptr)
{
	int k = 0;
	while(k < HLEDMRX_u8Speed)
	{
		HLEDMRX_voidDisplay(ptr);
		k++;
	}
}

void HLEDMRX_voidSetDisplaySpeed(u8 speed)
{
	HLEDMRX_u8Speed = speed;
}

void HLEDMRX_voidEnableShift(void)
{
	HLEDMRX_u8EnableShift = 1;
	staticImage = 0;
}

void HLEDMRX_voidDisableShift(void)
{
	HLEDMRX_u8EnableShift = 0;
	staticImage = 1 ;
}


/* void HLEDMRX_voidRshiftDisplay(void)
{
	while(HLEDMRX_u8EnableShift)
	{
		for( dataArrID=25 ; dataArrID>0 ; dataArrID--)
	    {
			STK_voidSetIntervalPeriodic(1000000 , HLEDMRX_voidSetDisplaySpeed);
			HLEDMRX_voidDisplay();
			if(dataArrID == 0)
			 		dataArrID=23;
	    }
	}
	STK_voidStopTimer();
}
*/
