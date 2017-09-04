/********************************************************************************************
File: QuadEnc.cpp
Description:
	
	Activates a hardware quadrature encoder interface on the Maple Mini with the STM32F103RCBT6 CORTEX-M3 MCU
	Channel A and Channel B are read on ports 27 and 26 (PA8 and PA9 respectively) and are counted on TIM1.
	Uses no additional librarys witch is great for portability and use of many open source projects.

Sources used:

  Maple mini documentation:
    http://docs.leaflabs.com/static.leaflabs.com/pub/leaflabs/maple-docs/0.0.12/hardware/maple-mini.html#maple-mini-stdocs
  STM32F103RCBT6 MCU documentation
    Datasheet:
      http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00161566.pdf
    Reference manual:
      http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/REFERENCE_MANUAL/CD00171190.pdf

Notes: get the memory map from the datasheet and the offsets for each paramater word in the reference manual 

Author: Fernando Figueiredo
License: GNU GPL
Creation: 2017-09-03
Last modification: 2017-09-03
********************************************************************************************/


#include "quadEnc.h"


/**
  * @brief  Initializes an instance of QuadEnc
  * @param  none
  * @retval None
  */
QuadEnc::QuadEnc()
{
	//Init pointer
	TIM1_CNT = (int*)(TIM1 + TIMx_CNT);
}


/**
  * @brief  Initializes encoder
  * @param  bInvertCountDir if true, counting direction will be inverted 
  * @retval None
  */
void QuadEnc::init_encoder(bool bInvertCountDir)
{
	//The following pointers will only be used once on startup, therefore they will be defined within
	//the function to free up memory once they are no longer necessary
	
	//Initiate pointers
	int *pointGPIOA_CRL = (int*)(GPIOA + GPIOx_CRL);
	int *pointGPIOA_CRH = (int*)(GPIOA + GPIOx_CRH);
	int *pointGPIOA_ODR = (int*)(GPIOA + GPIOx_ODR);
	
	//Configure PA8 and PA8 as inputs with pull up
	*pointGPIOA_CRH &= 0xFFFFFF00;
	*pointGPIOA_CRH |= 0x00000088;
  *pointGPIOA_ODR |= 0x00000300;
	

	//Initiate pointers
	int *TIM1_CR1 = (int*)(TIM1 + TIMx_CR1);
	int *TIM1_SMCR = (int*)(TIM1 + TIMx_SMCR);
	int *TIM1_CCMR1 = (int*)(TIM1 + TIMx_CCMR1);
	int *TIM1_CCER = (int*)(TIM1 + TIMx_CCER);

	//Configure timer	
  *TIM1_SMCR &= 0xFFFFFFF8;
	*TIM1_SMCR |= 0x00000003;
	*TIM1_CCMR1 &= 0xFFFFFCFC;
	*TIM1_CCMR1 |= 0x00000101;

	//If required, invert count direction
	if (bInvertCountDir)
	{
		//Set bit CC1P to invert polarity of CH1		
		*TIM1_CCER |= 0x00000002;
	}
	
  //Load value
	*TIM1_CNT = 0;
	
	//Enable timer
	//(Enablie is bit 0)
	*TIM1_CR1 |= 0x00000001;
}


/**
  * @brief  Initializes encoder
  * @param  None
  * @retval TIM1_CNT (Timer 1 counter)
  */
int QuadEnc::pos()
{
	return (*TIM1_CNT);
	
	/*switch(_iTIM)
	{
		case 1:
			return (*pointCNT1);
		case 2:
			return (*pointCNT2);
		case 3:
			return (*pointCNT3);
		case 4:
			return (*pointCNT4);
		default:
			return 0;
	}
	*/
}

/**
  * @brief  Loads value to Encoder Counter
  * @param  iNewCounterValue - Value to load to encoder counter
  * @retval None
  */
void QuadEnc::load_counter(int iNewCounterValue)
{
	//Initiate pointers
	int *TIM1_CR1 = (int*)(TIM1 + TIMx_CR1);
	
	//Disable timer
	//(Enablie is bit 0)
	*TIM1_CR1 &= 0xFFFFFFFE;
	
	//Load value
	*TIM1_CNT = iNewCounterValue;
	
	//Enable timer
	//(Enablie is bit 0)
	*TIM1_CR1 |= 0x00000001;
}
