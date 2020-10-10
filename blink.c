#include "stm32.h"

/* The code below sets up the timer, then on each timer interuupt
   flips the LED and outputs "blink X" over SWO, with X in 0..F */

/* Dummy variables to test .data and .bss initialization */
uint offset = 13;
uint count;

static inline void strb(volatile uint* reg, byte val)
{
	*((byte*)reg) = val;
}

static void swo_putc(char c)
{
	uint n = 10;

	if(!(ITM.TCR & BIT(0))) /* ITM disabled */
		return;
	if(!(ITM.TER & BIT(0))) /* port 0 disabled */
		return;
again:
	if(ITM.STIM[0]) /* SWO port is not-busy */
		goto write;

	if(--n > 0)
		goto again;
	else
		return; /* timeout, drop the char */
write:
	strb(&ITM.STIM[0], c);
}

static char hexchar(uint count)
{
	uint rem = count & 0xF;

	if(rem < 10)
		return '0' + rem;
	else
		return 'A' - 10 + rem;
}

static void report_blink(void)
{
	const char* p = "blink";
	char c;

	while((c = *p++))
		swo_putc(c);

	swo_putc(' ');
	swo_putc(hexchar(count+offset));
	swo_putc('\n');

	count++;
}

void irq_TIM2(void)
{
	int sr = TIM2.SR;

	if(!(sr & BIT(0))) /* no overflow condition */
		return;  /* skip spurious interrupt */

	TIM2.SR = sr & ~BIT(0); /* clear overflow flag */

	GPIOB.ODR ^= BIT(1); /* flip the led */

	report_blink();
}

static void start_clock(void)
{
	/* Set PLL multiplier 4 and HSE clock input */
	RCC.CFGR = BS(0b0010, 18) | BIT(16);

	/* Start HSE */
	RCC.CR |= BIT(16);
	/* Wait for HSE to settle */
	while(!(RCC.CR & BIT(17)));

	/* Start PLL */
	RCC.CR |= BIT(24);
	/* Wait for PLL to settle */
	while(!(RCC.CR & BIT(25)));

	/* Switch the system to use PLL as the clock source */
	RCC.CFGR = (RCC.CFGR & ~BS(0b11,0)) | BS(0b10,0);

	/* Wait until the system is running on PLL */
	while((RCC.CFGR & BS(0b11,2)) != BS(0b10,2));
}

void reset(void)
{
	/* Start peripheral clocks
	   We need TIM1 from APB1 and GPIOB from APB2 */
	RCC.APB2ENR = BIT(3);
	RCC.APB1ENR = BIT(0);

	/* Set mode for the LED pin (pin 1 output 2MHz) */
	/* Note reset value for CRL is 0x44444444 = all floating inputs */
	GPIOB.CRL = 0x44444424;

	start_clock();

	/* Enable TIM2 interrupt (position 28) */
	NVIC.ISER[0] = BIT(28);

	/* Set up the timer */
	TIM2.PSC = 16000;  /* prescaler 16000 => 2KHz counter */
	TIM2.ARR = 1000;   /* count to 1000 => 2Hz interrupts */
	TIM2.EGR = BIT(0); /* UG, update generation */
	TIM2.DIER = BIT(0); /* UIE, update interrupt enable */
	TIM2.CR1 = BIT(0); /* CEN, counter enable */
}
