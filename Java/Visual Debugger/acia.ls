   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
   4                     ; Optimizer V4.3.6 - 29 Nov 2011
2083                     ; 28 char getch(void)
2083                     ; 29 	{
2084                     	switch	.text
2085  0000               f_getch:
2087  0000 88            	push	a
2088       00000001      OFST:	set	1
2091  0001 ce0002        	ldw	x,_ptlec
2092  0004               L7631:
2093                     ; 32 	while (ptlec == ptecr)		/* equal pointers => loop */
2095  0004 c30000        	cpw	x,_ptecr
2096  0007 27fb          	jreq	L7631
2097                     ; 34 	c = *ptlec++;			/* get the received char */
2099  0009 f6            	ld	a,(x)
2100  000a 5c            	incw	x
2101                     ; 35 	if (ptlec >= &buffer[SIZE])	/* put in in buffer */
2103  000b a30044        	cpw	x,#_buffer+64
2104  000e 2503          	jrult	L3731
2105                     ; 36 		ptlec = buffer;
2107  0010 ae0004        	ldw	x,#_buffer
2108  0013               L3731:
2109  0013 cf0002        	ldw	_ptlec,x
2110                     ; 37 	return (c);
2114  0016 5b01          	addw	sp,#1
2115  0018 87            	retf	
2148                     ; 42 void outch(char c)
2148                     ; 43 	{
2149                     	switch	.text
2150  0019               f_outch:
2152  0019 88            	push	a
2153       00000000      OFST:	set	0
2156  001a               L3141:
2157                     ; 44 	while (!(USART_SR & TRDE))	/* wait for READY */
2159  001a 720f4a30fb    	btjf	_USART_SR,#7,L3141
2160                     ; 46 	USART_DR = c;			/* send it */
2162  001f 7b01          	ld	a,(OFST+1,sp)
2163  0021 c74a31        	ld	_USART_DR,a
2164                     ; 47 	}
2167  0024 84            	pop	a
2168  0025 87            	retf	
2194                     ; 53 @interrupt void recept(void)
2194                     ; 54 	{
2195                     	switch	.text
2196  0026               f_recept:
2200                     ; 55 	USART_SR;			/* clear interrupt */
2202  0026 c64a30        	ld	a,_USART_SR
2203                     ; 56 	*ptecr++ = USART_DR;		/* get the char */
2205  0029 ce0000        	ldw	x,_ptecr
2206  002c c64a31        	ld	a,_USART_DR
2207  002f f7            	ld	(x),a
2208  0030 5c            	incw	x
2209                     ; 57 	if (ptecr >= &buffer[SIZE])	/* put it in buffer */
2211  0031 a30044        	cpw	x,#_buffer+64
2212  0034 2503          	jrult	L7241
2213                     ; 58 		ptecr = buffer;
2215  0036 ae0004        	ldw	x,#_buffer
2216  0039               L7241:
2217  0039 cf0000        	ldw	_ptecr,x
2218                     ; 59 	}
2221  003c 80            	iret	
2262                     ; 65 void main(void)
2262                     ; 66 	{
2263                     	switch	.text
2264  003d               f_main:
2266  003d 89            	pushw	x
2267       00000002      OFST:	set	2
2270                     ; 68 	ptecr = ptlec = buffer;		/* initialize pointers */
2272  003e ae0004        	ldw	x,#_buffer
2273  0041 cf0002        	ldw	_ptlec,x
2274  0044 cf0000        	ldw	_ptecr,x
2275                     ; 69 	USART_BRR1 = 0xc9;		/* parameter for baud rate */
2277  0047 35c94a32      	mov	_USART_BRR1,#201
2278                     ; 70 	USART_CR1 = 0x00;		/* parameter for word length */
2280  004b 725f4a34      	clr	_USART_CR1
2281                     ; 71 	USART_CR2 = 0x2c;		/* parameters for interrupt */
2283  004f 352c4a35      	mov	_USART_CR2,#44
2284                     ; 72 	rim();				/* authorize interrupts */
2287  0053 9a            	rim	
2289                     ; 73 	h = showMeSillySection();
2291  0054 8d6b006b      	callf	f_showMeSillySection
2293  0058               L5441:
2294                     ; 75 		outch(getch());		/* get and put a char */
2296  0058 8d000000      	callf	f_getch
2298  005c 8d190019      	callf	f_outch
2301  0060 20f6          	jra	L5441
2332                     ; 79 int tryMe(int i) {
2333                     	switch	.text
2334  0062               f_tryMe:
2338                     ; 80   return i * 5;
2340  0062 90ae0005      	ldw	y,#5
2341  0066 8d000000      	callf	d_imul
2345  006a 87            	retf	
2368                     ; 83 int showMeSillySection(void) {
2369                     	switch	.text
2370  006b               f_showMeSillySection:
2374                     ; 84   return 10 + tryMe(6);
2376  006b ae0006        	ldw	x,#6
2377  006e 8d620062      	callf	f_tryMe
2379  0072 1c000a        	addw	x,#10
2382  0075 87            	retf	
2426                     	xdef	f_tryMe
2427                     	xdef	f_main
2428                     	xdef	f_recept
2429                     	xdef	f_outch
2430                     	xdef	f_getch
2431                     	switch	.bss
2432  0000               _ptecr:
2433  0000 0000          	ds.b	2
2434                     	xdef	_ptecr
2435  0002               _ptlec:
2436  0002 0000          	ds.b	2
2437                     	xdef	_ptlec
2438  0004               _buffer:
2439  0004 000000000000  	ds.b	64
2440                     	xdef	_buffer
2441                     	xdef	f_showMeSillySection
2442                     	xref.b	c_x
2462                     	xref	d_imul
2463                     	end
