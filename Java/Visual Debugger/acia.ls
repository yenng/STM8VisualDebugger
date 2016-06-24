   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
   4                     ; Optimizer V4.3.6 - 29 Nov 2011
2083                     ; 26 char getch(void)
2083                     ; 27 	{
2084                     	switch	.text
2085  0000               f_getch:
2087  0000 88            	push	a
2088       00000001      OFST:	set	1
2091  0001 ce0002        	ldw	x,_ptlec
2092  0004               L7631:
2093                     ; 30 	while (ptlec == ptecr)		/* equal pointers => loop */
2095  0004 c30000        	cpw	x,_ptecr
2096  0007 27fb          	jreq	L7631
2097                     ; 32 	c = *ptlec++;			/* get the received char */
2099  0009 f6            	ld	a,(x)
2100  000a 5c            	incw	x
2101                     ; 33 	if (ptlec >= &buffer[SIZE])	/* put in in buffer */
2103  000b a30044        	cpw	x,#_buffer+64
2104  000e 2503          	jrult	L3731
2105                     ; 34 		ptlec = buffer;
2107  0010 ae0004        	ldw	x,#_buffer
2108  0013               L3731:
2109  0013 cf0002        	ldw	_ptlec,x
2110                     ; 35 	return (c);
2114  0016 5b01          	addw	sp,#1
2115  0018 87            	retf	
2148                     ; 40 void outch(char c)
2148                     ; 41 	{
2149                     	switch	.text
2150  0019               f_outch:
2152  0019 88            	push	a
2153       00000000      OFST:	set	0
2156  001a               L3141:
2157                     ; 42 	while (!(USART_SR & TRDE))	/* wait for READY */
2159  001a 720f4a30fb    	btjf	_USART_SR,#7,L3141
2160                     ; 44 	USART_DR = c;			/* send it */
2162  001f 7b01          	ld	a,(OFST+1,sp)
2163  0021 c74a31        	ld	_USART_DR,a
2164                     ; 45 	}
2167  0024 84            	pop	a
2168  0025 87            	retf	
2194                     ; 51 @interrupt void recept(void)
2194                     ; 52 	{
2195                     	switch	.text
2196  0026               f_recept:
2200                     ; 53 	USART_SR;			/* clear interrupt */
2202  0026 c64a30        	ld	a,_USART_SR
2203                     ; 54 	*ptecr++ = USART_DR;		/* get the char */
2205  0029 ce0000        	ldw	x,_ptecr
2206  002c c64a31        	ld	a,_USART_DR
2207  002f f7            	ld	(x),a
2208  0030 5c            	incw	x
2209                     ; 55 	if (ptecr >= &buffer[SIZE])	/* put it in buffer */
2211  0031 a30044        	cpw	x,#_buffer+64
2212  0034 2503          	jrult	L7241
2213                     ; 56 		ptecr = buffer;
2215  0036 ae0004        	ldw	x,#_buffer
2216  0039               L7241:
2217  0039 cf0000        	ldw	_ptecr,x
2218                     ; 57 	}
2221  003c 80            	iret	
2252                     ; 63 void main(void)
2252                     ; 64 	{
2253                     	switch	.text
2254  003d               f_main:
2258                     ; 65 	ptecr = ptlec = buffer;		/* initialize pointers */
2260  003d ae0004        	ldw	x,#_buffer
2261  0040 cf0002        	ldw	_ptlec,x
2262  0043 cf0000        	ldw	_ptecr,x
2263                     ; 66 	USART_BRR1 = 0xc9;		/* parameter for baud rate */
2265  0046 35c94a32      	mov	_USART_BRR1,#201
2266                     ; 67 	USART_CR1 = 0x00;		/* parameter for word length */
2268  004a 725f4a34      	clr	_USART_CR1
2269                     ; 68 	USART_CR2 = 0x2c;		/* parameters for interrupt */
2271  004e 352c4a35      	mov	_USART_CR2,#44
2272                     ; 69 	rim();				/* authorize interrupts */
2275  0052 9a            	rim	
2277  0053               L1441:
2278                     ; 71 		outch(getch());		/* get and put a char */
2280  0053 8d000000      	callf	f_getch
2282  0057 8d190019      	callf	f_outch
2285  005b 20f6          	jra	L1441
2329                     	xdef	f_main
2330                     	xdef	f_recept
2331                     	xdef	f_outch
2332                     	xdef	f_getch
2333                     	switch	.bss
2334  0000               _ptecr:
2335  0000 0000          	ds.b	2
2336                     	xdef	_ptecr
2337  0002               _ptlec:
2338  0002 0000          	ds.b	2
2339                     	xdef	_ptlec
2340  0004               _buffer:
2341  0004 000000000000  	ds.b	64
2342                     	xdef	_buffer
2362                     	end
