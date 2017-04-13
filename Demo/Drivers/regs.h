#ifndef REGS_H_
#define REGS_H_

#define PBASE 0x3F000000 //Physical Address for BCM2837

#define GPFSEL1 	(PBASE+0x00200004)
#define GPPUD      	(PBASE+0x00200094)
#define GPPUDCLK0  	(PBASE+0x00200098)

#define AUX_ENABLES     (PBASE+0x00215004)
#define AUX_MU_IO_REG   (PBASE+0x00215040)
#define AUX_MU_IER_REG  (PBASE+0x00215044)
#define AUX_MU_IIR_REG  (PBASE+0x00215048)
#define AUX_MU_LCR_REG  (PBASE+0x0021504C)
#define AUX_MU_MCR_REG  (PBASE+0x00215050)
#define AUX_MU_LSR_REG  (PBASE+0x00215054)
#define AUX_MU_MSR_REG  (PBASE+0x00215058)
#define AUX_MU_SCRATCH  (PBASE+0x0021505C)
#define AUX_MU_CNTL_REG (PBASE+0x00215060)
#define AUX_MU_STAT_REG (PBASE+0x00215064)
#define AUX_MU_BAUD_REG (PBASE+0x00215068)

//interrupt control regs
#define BASE_INTC			(PBASE+0x0000B200)

typedef struct {
	unsigned long	IRQBasic;	// Pending 0
	unsigned long	Pending1;
	unsigned long	Pending2;
	unsigned long	FIQCtrl;
	unsigned long	Enable1;
	unsigned long	Enable2;
	unsigned long	EnableBasic;
	unsigned long	Disable1;
	unsigned long	Disable2;
	unsigned long	DisableBasic;
} INTC_REGS;

static volatile INTC_REGS * const intcRegs = (INTC_REGS *) (BASE_INTC);

//timer regs
#define portTIMER_BASE                    		( (unsigned long ) (PBASE+0x0000B400) )

typedef struct _BCM2835_TIMER_REGS {
	unsigned long LOD;
	unsigned long VAL;
	unsigned long CTL;
	unsigned long CLI;
	unsigned long RIS;
	unsigned long MIS;
	unsigned long RLD;
	unsigned long DIV;
	unsigned long CNT;
} TIMER_REGS;

static volatile TIMER_REGS * const timerRegs = (TIMER_REGS *) (portTIMER_BASE);

#endif /* REGS_H_ */
