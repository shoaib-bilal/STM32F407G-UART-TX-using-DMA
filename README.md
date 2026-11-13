Whenever the user presses onboard push button of STM32F407G PA0, USART2 transmits string Hello world\r\n via DMA2 Stream6 request. 

STM32f407G is programmed utilizing CIMSIS header.

1. USART2: Function uart2_init implements, PA2=TX PA3=RX, is configured with Baud rate=115200, 1 Start, 8 bit data and 1 stop bit. 
2. Button interrupt: Function button_init( ) implements: PA0 as push button, configured with alternate function AF7, with rising edge trigger. EXTI IMR bit 0, interrupt enabled. Port A is selected for line 0 in SYSCFG[0].
3. DMA1 stream6 channel 4 is utilized as per USART2.
4. DMA configuration, function dma1_init( ) implements below:
  a. Destination address is the address of USART data register.
  b. Data width 1 byte
  c. Direct mode disabled, FIFO enabled, threshold Full
  d. Source address pointer=Increment ; destination address pointer=No increment
  e. Burst mode disabled.
  d. Circular mode disabled.
  e. Data transfer direction, Memory to Peripheral
5. dma1_interrupt_configuration function enables the Transfer complete, half tx complete, Transfer error, Direct mode error, FIFO error interrupts in control and FIFO control registers.
6. After this, DMA1 Stream6 is enabled in function: dma1_enable( ) 
7. The EXTI0_IRQHandler which is button handler, has a delay for button debouncing. It clears pending bit in Pending register to avoid getting looped in interrupt. It then sets the DMAT(DMA enable transfer) bit in USART2 CR3 to trigger DMA to begin transmission.
8. Interrupts for Half complete, full complete, etc is triggered accordingly and handled in DMA1_Stream6_IRQHandler; where interrupt flag is also cleared for corresponding interrupt. Calls backs are also provided for the user application.
9. In full transfer complete call back function, NTDR( No of data register) is reloaded; DMAT bit of USART2 is cleared before enabling stream 6 again to prevent continuous transfer. 
8. Upon every press on the push button PA0, USART2 successfully transmits the string "Hello world\r\n" via DMA2
