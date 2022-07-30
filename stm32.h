typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned short ushort;

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#define BIT(n) (1<<(n))
#define BS(v,s) ((v)<<(s))

/* Ref. CM3-TRM #4 System Control

   These all are standalone registers in the docs, but keeping them
   all top-level would be impractical, so they got split into groups
   with reasonably small offsets from respective base addresses. */

extern volatile struct {
	uint _0;
	uint ICTR;
	uint ACTLR;
	uint _1;
	uint STCSR;
	uint STRVR;
	uint STCVR;
	uint STCR;
} SCS;

extern volatile struct {
	uint CPUID;
	uint ICSR;
	uint VTOR;
	uint AIRCR;
	uint SCR;
	uint CCR;
	uint SHP1;
	uint SHP2;
	uint SHP3;
	uint SHCSR;
	uint CFSR;
	uint HFSR;
	uint DFSR;
	uint MMFAR;
	uint BFAR;
	uint AFSR;
	uint PFR0;
	uint PFR1;
	uint DFR;
	uint ADR;
	uint MMFR0;
	uint MMFR1;
	uint MMFR2;
	uint MMFR3;
	uint ISAR0;
	uint ISAR1;
	uint ISAR2;
	uint ISAR3;
	uint ISAR4;
	uint _0[5];
	uint CPACR;
	uint _1[25];
	uint DHCSR;
	uint DCRSR;
	uint DCRDR;
	uint DEMCR;
} SCB;

/* Ref. CM3-TRM #5 Memory Protection Unit */

extern volatile struct {
	uint TYPE;
	uint CTRL;
	uint RNR;
	uint RBAR;
	uint RASR;
	uint RBAR_A1;
	uint RASR_A1;
	uint RBAR_A2;
	uint RASR_A2;
	uint RBAR_A3;
	uint RASR_A3;
} MPU;

/* Ref. CM3-TRM #6 Nested Vectored Interrupt Controller */

extern volatile struct {
	uint ISER[8];
	uint _0[24];
	uint ICER[8];
	uint _1[24];
	uint ISPR[8];
	uint _2[24];
	uint ICPR[8];
	uint _3[24];
	uint IABR[8];
	uint _4[56];
	uint IPR[20];
} NVIC;

extern volatile uint NVIC_STIR;

/* Ref. CM3-TRM #8 Data Watchpoint and Trace Unit */

extern volatile struct {
	uint CTRL;
	uint CYCCNT;
	uint CPICNT;
	uint EXCCNT;
	uint SLEEPCNT;
	uint LSUCNT;
	uint FOLDCNT;
	uint PCSR;

	struct {
		uint COMP;
		uint MASK;
		uint FUNC;
		uint _0;
	} BP[4];
} DWT;

/* Ref. CM3-TRM #9 Instrumentation Trace Macrocell Unit */

extern volatile struct {
	uint STIM[32];
	uint _0[864];
	uint TER;
	uint _1[15];
	uint TPR;
	uint _2[15];
	uint TCR;
} ITM;

/* Ref. RM0008 #6 Backup registers */

extern volatile struct {
	uint _0;
	uint DRx[10]; /* note the 42 DR registers are NOT contiguous! */
	uint RTCCR;
	uint CR;
	uint CSR;
	uint _1;
	uint _2;
	uint DRy[32];
} BKP;

/* Ref. RM0008 #8 L/M/H/XL-density reset and clock control */

extern volatile struct {
	uint CR;
	uint CFGR;
	uint CIR;
	uint APB2RSTR;
	uint APB1RSTR;
	uint AHBENR;
	uint APB2ENR;
	uint APB1ENR;
	uint BDCR;
	uint CSR;
} RCC;

/* Ref. RM0008 #9 General-purpose and alternate-function I/Os */

extern volatile struct {
	uint EVCR;
	uint MAPR;
	uint EXTICR1;
	uint EXTICR2;
	uint EXTICR3;
	uint EXTICR4;
	uint MAPR2;
} AFIO;

extern volatile struct {
	uint CRL;
	uint CRH;
	uint IDR;
	uint ODR;
	uint BSRR;
	uint BRR;
	uint LCKR;
} GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG;

/* Ref. RM0008 #10 Interrupts and events */

extern volatile struct {
	uint IMR;
	uint EMR;
	uint RTSR;
	uint FTSR;
	uint SWIER;
	uint PR;
} EXTI;

/* Ref. RM0008 #11 Analog-to-digital converter */

extern volatile struct {
	uint SR;
	uint CR1;
	uint CR2;
	uint SMPR1;
	uint SMPR2;
	uint JOFR1;
	uint JOFR2;
	uint JOFR3;
	uint JOFR4;
	uint HTR;
	uint LTR;
	uint SQR1;
	uint SQR2;
	uint SQR3;
	uint JSQR;
	uint JDR1;
	uint JDR2;
	uint JDR3;
	uint JDR4;
	uint DR;
} ADC1, ADC2, ADC3;

/* Ref. RM0008 #12 Digital-to-analog converter */

extern volatile struct {
	uint CR;
	uint SWTRIGR;
	uint DHR12R1;
	uint DHR12L1;
	uint DHR8R1;
	uint DHR12R2;
	uint DHR12L2;
	uint DHR8R2;
	uint DHR12RD;
	uint DHR12LD;
	uint DHR8RD;
	uint DOR1;
	uint DOR2;
} DAC;

/* Ref. RM0008 #13 Direct memory access controller */

extern volatile struct {
	uint ISR;
	uint IFCR;

	struct {
		uint CCR;
		uint CNDTR;
		uint CPAR;
		uint CMAR;
		uint _0;
	} ch[7];

} DMA1, DMA2;

/* Ref. RM0008 #14 Advanced-control timers (TIM1, TIM8)
               #15 General-purpose timers (TIM2 to TIM5)
               #16 General-purpose timers (TIM9 to TIM14)
	       #17 Basic timers (TIM6, TIM7) */

/* All timers share the same basic structure, but some registers
   and some bits are not usable on the lesser ones. Check RM0008
   for applicable registers and bits for each timer. */

extern volatile struct {
	uint CR1;
	uint CR2;
	uint SMCR;
	uint DIER;
	uint SR;
	uint EGR;
	uint CMCR1;
	uint CMCR2;
	uint CCER;
	uint CNT;
	uint PSC;
	uint ARR;
	uint RCR;
	uint CCR1;
	uint CCR2;
	uint CCR3;
	uint CCR4;
	uint BDTR;
	uint DCR;
	uint DMAR;
} TIM1, TIM2, TIM3, TIM4, TIM5, TIM6, TIM7, TIM8,
  TIM9, TIM10, TIM11, TIM12, TIM13, TIM14;

/* Ref. RM0008 #18 Real-time clock */

extern volatile struct {
	uint CRH;
	uint CRL;
	uint PRLH;
	uint PRLL;
	uint DIVH;
	uint DIVL;
	uint CNTH;
	uint CNTL;
	uint ALRH;
	uint ALRL;
} RTC;

/* Ref. RM0008 #19 Independent watchdog */

extern volatile struct {
	uint KR;
	uint PR;
	uint RLR;
	uint SR;
} IWDG;

/* Ref. RM0008 #20 Window watchdog */

extern volatile struct {
	uint CR;
	uint CFR;
	uint SR;
} WWDG;

/* Ref. RM0008 #21 NAND Flash/PC Card controller */

extern volatile struct {
	uint BCR1;
	uint BTR1;
	uint BCR2;
	uint BTR2;
	uint BCR3;
	uint BTR3;
	uint BCR4;
	uint BTR4;
	uint _0[16];

	uint PCR2;
	uint SR2;
	uint PMEM2;
	uint PATT2;
	uint _1;
	uint ECCR2;
	uint _2;
	uint _3;
	uint PCR3;
	uint SR3;
	uint PMEM3;
	uint PATT3;
	uint _4;
	uint ECCR3;
	uint _5;
	uint _6;
	uint PCR4;
	uint SR4;
	uint _7;
	uint PATT4;
	uint PIO4;
	uint _8[20];

	uint BWTR1;
	uint _a;
	uint BWTR2;
	uint _b;
	uint BWTR3;
	uint _c;
	uint BWTR4;
} FSMC;

/* Ref. RM0008 #22 Secure digital input/output interface */

extern volatile struct {
	uint POWER;
	uint CLKCR;
	uint ARG;
	uint CMD;
	uint RESPCMD;
	uint RESP1;
	uint RESP2;
	uint RESP3;
	uint RESP4;
	uint DTIMER;
	uint DLEN;
	uint DCTRL;
	uint DCOUNT;
	uint STA;
	uint ICR;
	uint MASK;
	uint _0[2];
	uint FIFOCNT;
	uint _1[13];
	uint FIFO;
} SDIO;

/* Ref. RM0008 #23 Universal serial bus full-speed device interace */

extern volatile struct {
	uint EP[16]; /* only the first 8 are actually valid */
	uint CNTR;
	uint ISTR;
	uint FNR;
	uint DADDR;
	uint BTABLE;
} USB;

extern volatile uint PMA[256];

/* Ref. RM0008 #24 Controller area network */

extern volatile struct {
	uint MCR;
	uint MSR;
	uint TSR;
	uint RF0R;
	uint RF1R;
	uint IER;
	uint ESR;
	uint BTR;
	uint _0[88];

	uint TI0R;
	uint TDT0R;
	uint TDL0R;
	uint TDH0R;
	uint TI1R;
	uint TDT1R;
	uint TDL1R;
	uint TDH1R;
	uint TI2R;
	uint TDT2R;
	uint TDL2R;
	uint TDH2R;
	uint RI0R;
	uint RDT0R;
	uint RDL0R;
	uint RDH0R;
	uint RI1R;
	uint RDT1R;
	uint RDL1R;
	uint RDH1R;
	uint _1[12];

	uint FMR;
	uint FM1R;
	uint _2;
	uint FS1R;
	uint _3;
	uint FFA1R;
	uint _4;
	uint FA1R;
	uint _5[8];

	struct {
		uint R1;
		uint R2;
	} F[28];
} CAN1, CAN2;

/* Ref. RM0008 #25 Serial peripheral interface */

extern volatile struct {
	uint CR1;
	uint CR2;
	uint SR;
	uint DR;
	uint CPCPR;
	uint RXCRCR;
	uint TXCRCR;
	uint I2SCFGR;
	uint I2SPR;
} SPI1, SPI2, SPI3;

/* Ref. RM0008 #26 Inter-integrated circuit (I2C) interface */

extern volatile struct {
	uint CR1;
	uint CR2;
	uint OAR1;
	uint OAR2;
	uint DR;
	uint SR1;
	uint SR2;
	uint CCR;
	uint TRISE;
} I2C1, I2C2;

/* Ref. RM0008 #27 Universal synchronous asynchronous receiver transmitter */

extern volatile struct {
	uint SR;
	uint DR;
	uint BRR;
	uint CR1;
	uint CR2;
	uint CR3;
	uint GTPR;
} USART1, USART2, USART3;

/* Ref. PM0075 #3 Register description */

extern volatile struct {
	uint ACR;
	uint KEYR;
	uint OPTKEYR;
	uint SR;
	uint CR;
	uint AR;
	uint _1;
	uint OBR;
	uint WRPR;
} FLASH;


static inline void enable_irq(void)
{
	asm volatile ("cpsie i" : : : "memory");
}

static inline void disable_irq(void)
{
	asm volatile ("cpsid i" : : : "memory");
}
