/*
 * stm32_it.c
 *
 *  Created on: Nov 11, 2026
 *      Author: bilal
 */
#include"stm32f407xx.h"

/*
static int is_it_HT(void);
static int is_it_FT(void);
static int is_it_TE(void);
static int is_it_FE(void);
static int is_it_DME(void);
*/

#define is_it_HT()   DMA1->HISR & 1<<20
#define is_it_FT()   DMA1->HISR & 1<<21
#define is_it_TE()   DMA1->HISR & 1<<19
#define is_it_FE()   DMA1->HISR & 1<<22
#define is_it_DME()  DMA1->HISR & 1<<19

extern void HT_CompleteCallBack(void);
extern void FT_CompleteCallBack(void);
extern void TE_ErrorCallBack(void);
extern void FE_ErrorCallBack(void);
extern void DME_ErrorCallBack(void);



void EXTI0_IRQHandler(void)
{

	EXTI_TypeDef *pEXTI= EXTI;
	pEXTI->IMR &= ~(1<<0);
	for(uint32_t i=0;i<600000;i++);
	pEXTI->IMR |=  (1<<0);
	pEXTI->PR |= 1<<0;    //Clear EXTI pending bit position 0 by programming it to 1



	USART_TypeDef *pUSART2=USART2;

	pUSART2->CR3 |= 1<<7;

}

void DMA1_Stream6_IRQHandler(void)
{
	if(is_it_HT())
	{
		DMA1->HIFCR |= 1<<20;
		HT_CompleteCallBack();
	}
	else if(is_it_FT())
	{
		DMA1->HIFCR |= 1<<21;
		FT_CompleteCallBack();
	}
	else if(is_it_TE())
	{
		DMA1->HIFCR |= 1<<19;
		TE_ErrorCallBack();
	}
	else if(is_it_FE())
	{
		DMA1->HIFCR |= 1<<16;
		FE_ErrorCallBack();
	}
	else if(is_it_DME())
	{
		DMA1->HIFCR |= 1<<18;
		DME_ErrorCallBack();
	}
	else
	{
		;
	}

}

/*
static int is_it_HT(void)
{
	DMA_TypeDef *pDMA1=DMA1;

 return pDMA1->HISR & 1<<20;
}

static int is_it_FT(void)
{
	DMA_TypeDef *pDMA1=DMA1;

    return pDMA1->HISR & 1<<21;
}

static int is_it_TE(void)
{
	DMA_TypeDef *pDMA1=DMA1;

    return pDMA1->HISR & 1<<19;
}

static int is_it_FE(void)
{
	DMA_TypeDef *pDMA1=DMA1;

    return pDMA1->HISR & 1<<22;
}

static int is_it_DME(void)
{

	DMA_TypeDef *pDMA1=DMA1;

    return pDMA1->HISR & 1<<18;
}
*/
