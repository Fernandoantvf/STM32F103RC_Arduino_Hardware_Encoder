# STM32F103RC_Arduino_Hardware_Encoder
A simple library to enable hardware quadrature counting of an AB encoder 

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
