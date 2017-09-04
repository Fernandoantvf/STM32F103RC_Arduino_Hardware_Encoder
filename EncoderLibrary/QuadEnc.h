/********************************************************************************************
File: QuadEnc.h
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

#ifndef QuadEncoder_h
#define QuadEncoder_h

	//Port definitions
	#define GPIOA 0x40010800 //Port A start position
	#define GPIOB 0x40010C00 //Port B start position
	#define GPIOC 0x40011000 //Port C start position
	#define GPIOx_CRL 0x00 //Port configuration low rw
	#define GPIOx_CRH 0x04 //Port configuration high rw
	#define GPIOx_IDR 0x08 //Port input data register r
	#define GPIOx_ODR 0x0C //Port output data register rw

	//Timer definitions
	#define TIM1 0x40012C00 //Timer 1 start position
	#define TIM2 0x40000000 //Timer 2 start position
	#define TIM3 0x40000400 //Timer 3 start position
	#define TIM4 0x40000800 //Timer 4 start position	
	#define TIMx_CR1  0x00 //Timer control register 1 (Enablie is bit 0)
	#define TIMx_CR2  0x04 //Timer control register 2
	#define TIMx_SMCR 0x08 //Timer slave mode control register (SMS=’011’ count transitions on both channels are the 3 LSBs)
	#define TIMx_DIER 0x0C //Timer DMA/interrupt enable register
	#define TIMx_SR   0x10 //Timer status register 
	#define TIMx_EGR  0x14 //Timer event generation register
	#define TIMx_CCMR1 0x18 //Timer capture/compare mode register 1 (CC1S=’01’ TI1FP1 mapped on TI1 are the 2 LSBs)(CC2S=’01’ TI2FP1 mapped on TI2 are bits 9 and 8).
	#define TIMx_CCMR2 0x1C //Timer capture/compare mode register 2 .
	#define TIMx_CCER 0x20 //Timer capture/compare enable register (CC1P and CC2P define polarity)
	#define TIMx_CNT 0x24 //Timer counter
	#define TIMx_PSC 0x28 //Timer prescaler
	#define TIMx_ARR 0x2C //Timer auto-reload register
	#define TIMx_RCR 0x30 //Timer repetition counter register
	#define TIMx_CCR1 0x34 //Timer capture/compare register 1 
	#define TIMx_CCR2 0x38 //Timer capture/compare register 2	
	#define TIMx_CCR3 0x3C //Timer capture/compare register 3
	#define TIMx_CCR4 0x40 //Timer capture/compare register 4
	#define TIMx_BDTR 0x44 //Timer break and dead-time register
	#define TIMx_DCR 0x48 //Timer DMA control register
	#define TIMx_DMAR 0x48 //Timer DMA address for full transfer
	
	
class QuadEnc
{
  public:
		QuadEnc();
    void init_encoder(bool);
		void load_counter(int);
		int pos();
	private:
		// Pointer to Timer 1 counter
		// This pointer will be oftenly used so we declare it here
		// resulting in only one initiation and permanantly odcupying 32bit of memory.
		int *TIM1_CNT;
};

#endif