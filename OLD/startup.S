.extern	system_init
.extern __bss_start
.extern __bss_end
.extern FreeRTOS_IRQ_Handler
//.extern vPortYieldProcessor
.extern irqBlock
.extern main
	.section .init
	.globl _start
;;
_start:
	/* All the following instruction should be read as:	*/
	/* Load the address at symbol into the program counter.	*/
	
	/*	ldr	pc,reset_handler		/* 	Processor Reset handler 		-- we will have to force this on the raspi!	*/
	B reset_handler	
	/*	Because this is the first instruction executed, of cause it causes an immediate branch into reset!	*/
	
	/*	ldr pc,undefined_handler	/* 	Undefined instruction handler 	-- processors that don't have thumb can emulate thumb!	*/
	B undefined_handler
	/*	ldr pc,swi_handler			/* 	Software interrupt / TRAP (SVC) -- system SVC handler for switching to kernel mode.	*/
//	B swi_handler	
	/*	ldr pc,prefetch_handler		/*	Prefetch/abort handler.	*/
	B prefetch_handler	
	/*	ldr pc,data_handler			/* 	Data abort handler/	*/
	B data_handler
	/*	ldr pc,unused_handler		/* 	-- Historical from 26-bit addressing ARMs -- was invalid address handler.	*/
	B unused_handler
	/*	ldr pc,irq_handler			/* 	IRQ handler		*/
	B irq_handler
	/*	ldr pc,fiq_handler			/* 	Fast interrupt handler.	*/
	B fiq_handler

	/*	Here we create an exception address table! This means that reset/hang/irq can be absolute addresses	*/
reset_handler:      .word reset
undefined_handler:  .word undefined_instruction
//swi_handler:        .word vPortYieldProcessor
prefetch_handler:   .word prefetch_abort
data_handler:       .word data_abort
unused_handler:     .word unused
irq_handler:        .word FreeRTOS_IRQ_Handler
fiq_handler:        .word fiq

reset:
	/*	In the reset handler, we need to copy our interrupt vector table to 0x0000, its currently at 0x8000	*/

	mov x0,#0x8000			/*	Store the source pointer	*/
	mov x1,#0x0000			/*	Store the destination pointer.	*/

	/*	Here we copy the branching instructions	*/
	/*LDP w2,w3,w4,w5,w6,w7,w8,w9,[w0!], #16			/*	Load multiple values from indexed address. 		Auto-increment R0	*/
	LDR x2,[x0], #16
	LDR x3,[x0], #16
	LDR x4,[x0], #16
	LDR x5,[x0], #16
	LDR x6,[x0], #16
	LDR x7,[x0], #16
	LDR x8,[x0], #16
	LDR x9,[x0]
	/*STP w2,w3,w4,w5,w6,w7,w8,w9,[w1!], #16			/*	Store multiple values from the indexed address.		Auto-increment R1	*/
	STR x2,[x1], #16
	STR x3,[x1], #16
	STR x4,[x1], #16
	STR x5,[x1], #16
	STR x6,[x1], #16
	STR x7,[x1], #16
	STR x8,[x1], #16
	STR x9,[x1]

	/*	So the branches get the correct address we also need to copy our vector table!	*/
    	/*LDP w2,w3,w4,w5,w6,w7,w8,w9,[w0!], #16			/* Load from 4*n of regs (8) as R0 is now incremented.	*/
    	LDR x2,[x0], #16
	LDR x3,[x0], #16
	LDR x4,[x0], #16
	LDR x5,[x0], #16
	LDR x6,[x0], #16
	LDR x7,[x0], #16
	LDR x8,[x0], #16
	LDR x9,[x0]
	/*STP w2,w3,w4,w5,w6,w7,w8,w9,[w1!], #16			/* Store this extra set of data.				*/
	STR x2,[x1], #16
	STR x3,[x1], #16
	STR x4,[x1], #16
	STR x5,[x1], #16
	STR x6,[x1], #16
	STR x7,[x1], #16
	STR x8,[x1], #16
	STR x9,[x1]

	/*	Set up the various STACK pointers for different CPU modes	*/
	/*	(PSR_IRQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)	*/
	mov x0,#0xD2
	msr NZCV,x0
	mov sp,#0x8000

	/*	(PSR_FIQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)	*/
	mov x0,#0xD1
	msr NZCV,x0
	mov sp,#0x4000

	/*	(PSR_SVC_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)	*/
	mov x0,#0xD3
	msr NZCV,x0
	mov sp,#0x8000000

	ldr x0, =__bss_start
	ldr x1, =__bss_end

	mov x2, #0

zero_loop:
	cmp 	x0,x1
	//it		lt		Replaced by GE and a label "skip"
	BGE skip	
	STR	x2,[x0],#16
skip:
	blt		zero_loop

	bl 		irqBlock
	
	
	/* 	mov	sp,#0x1000000	*/
	b main				/*	We're ready?? Lets start main execution!	*/
	.section .text

undefined_instruction:
	b undefined_instruction

prefetch_abort:
	b prefetch_abort

data_abort:
	b data_abort

unused:
	b unused

fiq:
	b fiq
	
hang:
	b hang

