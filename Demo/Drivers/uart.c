#include "regs.h"

static void PUT32 ( unsigned int addr, unsigned int value)
{
    *(unsigned int *)addr = value;
}

static unsigned int GET32 ( unsigned int addr)
{
    return *(unsigned int *)addr;
}

static void dummy ( unsigned int value)
{
    (void)value;
    return;
}

static void uart_send ( unsigned int c )
{
    //int i;
    while(1)
    {
        if(GET32(AUX_MU_LSR_REG)&0x20) break;
    }
    //for(i=0;i<0x7FF;i++);
    PUT32(AUX_MU_IO_REG,c);
}

void uart_init ( void )
{
    unsigned int ra;

    PUT32(AUX_ENABLES,1);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_CNTL_REG,0);
    PUT32(AUX_MU_LCR_REG,3);
    PUT32(AUX_MU_MCR_REG,0);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_IIR_REG,0xC6);
    PUT32(AUX_MU_BAUD_REG,270);
    ra=GET32(GPFSEL1);
    ra&=~(7<<12); //gpio14
    ra|=2<<12;    //alt5
    ra&=~(7<<15); //gpio15
    ra|=2<<15;    //alt5
    PUT32(GPFSEL1,ra);
    PUT32(GPPUD,0);
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,(1<<14)|(1<<15));
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,0);
    PUT32(AUX_MU_CNTL_REG,3);
}

void uart_puts (char* s)
{
	while(*s!=0)
    {
    	uart_send((unsigned int)*s);
    	s++;
    }
	uart_send(0x0D);
	uart_send(0x0A);
}
