.section .text
.syntax unified
.thumb
.align 2

.globl start_reset

.macro thumb addr
	.word \addr + 1
.endm

.macro stub
	thumb 4f // the wfi instruction below
.endm

// Ref. RM0008 #10.1.2 Interrupt and exception vectors

initial_stack_ptr:
        .word RAM_end         //  0 (stack)
interrupt_vectors:
        thumb start_reset     //  1 Reset
        stub                  //  2 NMI
        stub                  //  3 HardFault
        stub                  //  4 MemManage
        stub                  //  5 BusFault
        stub                  //  6 UsageFault
	stub                  //  7 (reserved)
	stub                  //  8 (reserved)
	stub                  //  9 (reserved)
	stub                  // 10 (reserved)
	stub                  // 11 SVCall
	stub                  // 12 Debug Monitor
	stub                  // 13 (reserved)
	stub                  // 14 PendSV
	stub                  // 15 SysTick
peripheral_vectors:
	stub                  //  0 WWDG
	stub                  //  1 PVD
	stub                  //  2 TAMPER
	stub                  //  3 RTC
	stub                  //  4 FLASH
	stub                  //  5 RCC
	stub                  //  6 EXTI0
	stub                  //  7 EXTI1
	stub                  //  8 EXTI2
	stub                  //  9 EXTI3
	stub                  // 10 EXTI4
	stub                  // 11 DMA1_Channel1
	stub                  // 12 DMA1_Channel2
	stub                  // 13 DMA1_Channel3
	stub                  // 14 DMA1_Channel4
	stub                  // 15 DMA1_Channel5
	stub                  // 16 DMA1_Channel6
	stub                  // 17 DMA1_Channel7
	stub                  // 18 ADC1_2
	stub                  // 19 USB_HP / CAN1_TX
	stub                  // 20 USB_LP / CAN1_RX0
	stub                  // 21 CAN1_RX1
	stub                  // 22 CAN1_SCE
	stub                  // 23 EXTI9_5
	stub                  // 24 TIM1_BRK
	stub                  // 25 TIM1_UP
	stub                  // 26 TIM1_TRG_COM
	stub                  // 27 TIM1_CC
	thumb irq_TIM2        // 28 TIM2
	stub                  // 29 TIM3
	stub                  // 30 TIM4
	stub                  // 31 I2C1_EV
	stub                  // 32 I2C1_ER
	stub                  // 33 I2C2_EV
	stub                  // 34 I2C2_ER
	stub                  // 35 SPI1
	stub                  // 36 SPI2
	stub                  // 37 USART1
	stub                  // 38 USART2
	stub                  // 39 USART3
	stub                  // 40 EXTI15_10
	stub                  // 41 RTCAlarm
	stub                  // 42 USBWakeup
	stub                  // 43 TIM8_BRK
	stub                  // 44 TIM8_UP
	stub                  // 45 TIM8_TRG_COM
	stub                  // 46 TIM8_CC
	stub                  // 47 ADC3
	stub                  // 48 FSMC
	stub                  // 49 SDIO
	stub                  // 50 TIM5
	stub                  // 51 SPI3
	stub                  // 52 UART4
	stub                  // 53 UART5
	stub                  // 54 TIM6
	stub                  // 55 TIM7
	stub                  // 56 DMA2_Channel1
	stub                  // 57 DMA2_Channel2
	stub                  // 58 DMA2_Channel3
	stub                  // 59 DMA2_Channel4_5

start_reset:
	ldr.n r1, 5f+0x4 // RAM_org
	ldr.n r2, 5f+0x8 // RAM_bss
	ldr.n r3, 5f+0x0 // ROM_brk
	// copy .data from ROM to RAM
0:	subs r4, r1, r2
	bcs.n 1f
	ldr.n r0, [r3]
	str.n r0, [r1]
	adds r3, $4
	adds r1, $4
	b 0b
	// zero-fill .bss
1:	ldr.n r2, 5f+0xC // RAM_brk
	movs r0, $0
2:	subs r4, r1, r2
	bcs.n 3f
	str.n r0, [r1]
	adds r1, $4
	b 2b
	// jump to the C code
3:	bl reset
        // fallthrough
4:	wfi
	b 4b
	nop

5:	.word ROM_brk
	.word RAM_org
	.word RAM_bss
	.word RAM_brk
