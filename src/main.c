/***** Project Description
 * Play an audio and display shapes on led matrix at the same time
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO.h"
#include "STK_Interface.h"

#include "LEDMRX_interface.h"
#include "DAC_interface.h"

#include "../include/audio.h"


u8 shape1[8] = {32, 144, 75, 63, 75, 144, 32, 0};
u8 shape2[8] = {2, 36, 75, 63, 75, 36, 2, 0};


void play(void)
{
	DAC_voidReadAudioArrAsync(audioSession_raw, 38359);
}

int main(void)
{
	/* RCC init */
	RCC_voidInitSysClock();/* initiate clock as HSE */
	RCC_voidEnableClock(RCC_APB2 , 2);/* enable GPIOA */
	RCC_voidEnableClock(RCC_APB2 , 3);/* enable GPIOB */


	/* GPIOA init (SET Directions) */
	DIO_Init();

	HLEDMRX_voidInit();
	HLEDMRX_voidDisableShift(); // Static Image - No shift

   MSTK_voidInit();/* initiate timer clk AHP/8 */

   MSTK_voidSetIntervalPeriodic(125,play);

   u32 i;
	while(1)
	{
		HLEDMRX_voidShowStatic(shape1);
		for(i=0; i<10000; i++); // 10 ms

		HLEDMRX_voidShowStatic(shape2);
		for(i=0; i<10000; i++); // 10 ms

	}
}
