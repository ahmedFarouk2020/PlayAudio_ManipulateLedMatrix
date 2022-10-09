/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 31 2020                              */
/*********************************************************/

#ifndef LEDMRX_INTERFACE_H
#define LEDMRX_INTERFACE_H


#define TO_LEFT    0
#define TO_RIGHT   1

/* INITIALIZE PIN DIRECTION MODE (output) */
void HLEDMRX_voidInit(void);
/* display a shape -->  */
void HLEDMRX_voidDisplay(u8 *copy_u8Data);
/* to display arabic word or thing will be right shift */
void HLEDMRX_voidRshiftDisplay(void);
/* to display arabic word or thing will be left shifted */
void HLEDMRX_voidLshiftDisplay(void);
/* enable shift display functions */
void HLEDMRX_voidEnableShift(void);
/* disable shift display functions */
void HLEDMRX_voidDisableShift(void);
/* controls speed of shifting */
void HLEDMRX_voidSetDisplaySpeed(u8 speed);

void HLEDMRX_voidShift(u8 *ptr, u8 SentenceWidth, u8 shift_direction);

/* Display static shape */
void HLEDMRX_voidShowStatic(u8 *ptr);

void _2ms_delay(void);


#endif
