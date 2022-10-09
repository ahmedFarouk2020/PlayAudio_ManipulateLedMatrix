/*
 * DIO_Cfg.c
 *
 *  Created on: Mar 23, 2022
 *      Author: moham
 */

#include "../include/STD_TYPES.h"
#include "../include/DIO_Cfg.h"

const DIO_ChannelConfigType DIO_ConfigParam[DIO_NUM_OF_CHANNELS] =
{

  {0,11,2,1,0},   /* channel0 - row0 */
  {0,1,2,1,0},   /* channel1 - row1 */
  {0,2,2,1,0},  /* channel2 - row2 */
  {0,3,2,1,0},   /* channel3 - row3 */
  {0,4,2,1,0},   /* channel4 - row4 */
  {0,5,2,1,0},  /* channel5 - row5 */
  {0,6,2,1,0},   /* channel6 - row6 */
  {0,7,2,1,0},   /* channel7 - row7 */
  {1,0,2,1,0},  /* channel8 - col0 */
  {1,1,2,1,0},   /* channel9 - col1 */
  {1,5,2,1,0},   /* channel10 - col2 */
  {1,6,2,1,0},  /* channel11 - col3 */
  {1,7,2,1,0},   /* channel12 - col4 */
  {1,8,2,1,0},   /* channel13 - col5 */
  {1,9,2,1,0},  /* channel14 - col6 */
  {1,10,2,1,0},   /* channel15 - col7 */

	{0,8,2,1,0},  /* Channel 16 - DAC 0 */
	{0,9,2,1,0},   /* Channel 17 - DAC 1 */
	{0,10,2,1,0},   /* Channel 18 - DAC 2 */
	{0,12,2,1,0},  /* Channel 19 - DAC 3 */
	{0,15,2,1,0},  /* Channel 20 - DAC 4 */
	{1,13,2,1,0},  /* Channel 21 - DAC 5 */
	{1,14,2,1,0},  /* Channel 22 - DAC 6 */
	{1,15,2,1,0},  /* Channel 23 - DAC 7 */
	{0,0,0,1,0}  /* Channel 24 - EXTI0 */

};


const DIO_ChannelGroupConfigType DIO_ChannelGroupList[DIO_NUM_OF_CHANNELGROUPS] = {
		{
				{0,1,2,3,4,5,6,7}, /* ROWS */
				8
		},
		{
				{8,9,10,11,12,13,14,15}, /* COLS */
				8
		},
		{
				{16,17,18,19,20,21,22,23}, /* DAC */
				8
		}
};
