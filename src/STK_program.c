/*****************************************/
/* Author  :  Ahmed Assaf                */
/* Version :  V01                        */
/* Date    : 26 August 2020              */
/*****************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"


#define CLK_SRC    MSTK_CLK_SRC
#define TIMER_FREQ    (F_CPU/CLK_SRC)


#define MS_TO_TICKS(n_ms)     (u32)((n_ms/1000.0)*TIMER_FREQ)
#define US_TO_TICKS(n_us)     (u32)( (n_us * TIMER_FREQ) /1000000.0 )
#define TICKS_TO_MS(n_ticks)  (u32)(((double)n_ticks/TIMER_FREQ)*1000)
#define TICKS_TO_US(n_ticks)  (u32)( ((double)n_ticks * 1000000.0/TIMER_FREQ))//(u32)(  (  ((double)n_ticks/TIMER_FREQ)  *  1000.0) * 1000.0)



/* Define Callback Global Variable */
static void(*MSTK_CallBack)(void);

/* Define Variable for interval mode */
static u8 MSTK_u8ModeOfInterval;

void MSTK_voidInit(void)
{
#if MSTK_CLK_SRC == MSTK_SRC_AHB
    /* Disable STK - Disable STK Interrupt - Set clock source AHB */
	MSTK -> CTRL = 0x00000004;
#elif MSTK_CLK_SRC == MSTK_SRC_AHB_8
    /* Disable STK - Disable STK Interrupt - Set clock source AHB/8 */
	MSTK -> CTRL = 0;
#else
	#error "Invalid Clock Configuration"
	
#endif
}

void MSTK_voidSetBusyWait( u32 Copy_u32ms)
{
	u32 Copy_u32Ticks = MS_TO_TICKS(Copy_u32ms);
	if(Copy_u32Ticks > 0xffffff) {
		Copy_u32Ticks = 0xffffff;
	}
	/* Load ticks to load register */
	MSTK -> LOAD = Copy_u32Ticks;
	
	/* Start Timer */
	SET_BIT(MSTK->CTRL, 0);
	
	/* Wait till flag is raised */
	while( (GET_BIT(MSTK->CTRL,16)) == 0);
	
	/* Stop Timer */
	SET_BIT(MSTK->CTRL, 0);
	MSTK -> LOAD = 0;
	MSTK -> VAL  = 0;
	
}

void MSTK_voidSetIntervalSingle  ( u32 Copy_u32ms, void (*Copy_ptr)(void) )
{
	u32 Copy_u32Ticks = MS_TO_TICKS(Copy_u32ms);
	/* Disable Timer */
	CLR_BIT(MSTK->CTRL,0);
	MSTK -> VAL = 0;

	/* Load ticks to load register */
	MSTK -> LOAD = Copy_u32Ticks;
	
	/* Start Timer */
	SET_BIT(MSTK->CTRL, 0);
	
	/* Save CallBack */
	MSTK_CallBack = Copy_ptr;
	
	/* Set Mode to Single */
	MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;
	
	/* Enable STK Interrupt */
	SET_BIT(MSTK->CTRL, 1);
}

void MSTK_voidSetIntervalPeriodic( u32 Copy_u32us, void (*Copy_ptr)(void) )
{
	u32 Copy_u32Ticks = US_TO_TICKS(Copy_u32us);
	/* Load ticks to load register */
	MSTK -> LOAD = Copy_u32Ticks;
	
	/* Start Timer */
	SET_BIT(MSTK->CTRL, 0);
	
	/* Save CallBack */
	MSTK_CallBack = Copy_ptr;
	
	/* Set Mode to Single */
	MSTK_u8ModeOfInterval = MSTK_PERIOD_INTERVAL;
	
	/* Enable STK Interrupt */
	SET_BIT(MSTK->CTRL, 1);
}

void MSTK_voidStopInterval(void)
{
	/* Disable STK Interrupt */
	CLR_BIT(MSTK->CTRL, 1);
	
	/* Stop Timer */
	SET_BIT(MSTK->CTRL, 0);
	MSTK -> LOAD = 0;
	MSTK -> VAL  = 0;
}

/*
 * Return time in u seconds
 */
u32  MSTK_u32GetElapsedTime(void)
{
	u32 Local_u32ElapsedTimeInTicks;
	
	Local_u32ElapsedTimeInTicks = MSTK->LOAD - MSTK->VAL ;
	
	return TICKS_TO_US(Local_u32ElapsedTimeInTicks);
}



/*
 * Return time in u seconds
 */
u32  MSTK_u32GetRemainingTime(void)
{
	u32 Local_u32RemainTimeInTicks;
	
	Local_u32RemainTimeInTicks = MSTK->VAL ;
	
	return TICKS_TO_US(Local_u32RemainTimeInTicks);
}

void SysTick_Handler(void)
{
	u8 Local_u8Temporary;
	
	if (MSTK_u8ModeOfInterval == MSTK_SINGLE_INTERVAL)
	{
		/* Disable STK Interrupt */
		CLR_BIT(MSTK->CTRL, 1);
	
		/* Stop Timer */
		SET_BIT(MSTK->CTRL, 0);
		MSTK -> LOAD = 0;
		MSTK -> VAL  = 0;
	}
	
	/* Callback notification */
	MSTK_CallBack();
	
	/* Clear interrupt flag */
	Local_u8Temporary = GET_BIT(MSTK->CTRL,16);
}

void MSTK_voidResetTimer(void)
{
	MSTK->VAL = 0;
}
