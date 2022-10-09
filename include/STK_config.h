/*****************************************/
/* Author  :  Ahmed Assaf                */
/* Version :  V01                        */
/* Date    :  26 August 2020             */
/*****************************************/
#ifndef STK_CONFIG_H
#define STK_CONFIG_H

#warning "Set the F_CPU with the correct value to make system work properly!"
#define F_CPU    8000000U  /* Configure this */



#define     MSTK_SRC_AHB           1
#define     MSTK_SRC_AHB_8         8
/* Options: MSTK_SRC_AHB / MSTK_SRC_AHB_8 */
#define MSTK_CLK_SRC     MSTK_SRC_AHB_8 /* Configure this */


#endif
