/*********************************************************/
/* author  : Farouk                                      */
/* Version : v02                                         */
/* Date    : July 25 2022                              */
/*********************************************************/


#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

#include "STD_TYPES.h"
#include "BIT_MATH.h"


#define GPIOA_BASE_ADDRESS   (0x40010800)
#define GPIOB_BASE_ADDRESS   (0x40010C00)
#define GPIOC_BASE_ADDRESS   (0x40011000)

typedef struct DIO_REG
{
    volatile u32 CRL;
    volatile u32 CRH;
    volatile u32 IDR;
    volatile u32 ODR;
    volatile u32 BSRR;
    volatile u32 BRR;
    volatile u32 LCK;
}GPIO_TypeDef;

// GPIO_TypeDef* GPIOA = (GPIO_TypeDef*)GPIOA_BASE_ADDRESS;
// GPIO_TypeDef* GPIOB = (GPIO_TypeDef*)GPIOB_BASE_ADDRESS;
// GPIO_TypeDef* GPIOC = (GPIO_TypeDef*)GPIOC_BASE_ADDRESS;


#endif
