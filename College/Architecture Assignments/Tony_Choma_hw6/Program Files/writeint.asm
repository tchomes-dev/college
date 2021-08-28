conv:   lodd c10:	;starts the conversion from decimal to ascii
        push		;by loading 10 to stack and then the dividend
        lodd sum:	;this gives single digit numbers of the decimal
        push		
        div		
        lodd digits:
        addd c1:
        stod digits:
conv2:  pop		;loop so it handle multi-digit numbers
	    jzer out:
	    stod temp:	
        lodd c10:
        push
        lodd temp:
        push
        div
	    pop
	    stod a:
	    pop
	    stod b:
	    insp 2		;incrementing sp because div() doesnt do it and I wasted 5 hours wondering why.
	    lodd b:		;this allows for easy streamlined "popping" to the transmitter buffer
	    push
	    lodd a:
	    push
        lodd digits:
        addd c1:
        stod digits:
        jump conv2:
out:    lodd sum:
        jneg over:
        lodd on:
        stod 4095
        call xbsywt:
        pop
	    addd numoff:	;add 48 to convert to ascii
out2:   stod 4094
        lodd digits:
        subd c1:
        stod digits:
        jzer end:
	    jneg end:
        pop
	    addd numoff:
        jump out2: