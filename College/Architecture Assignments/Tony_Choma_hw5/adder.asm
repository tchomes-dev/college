start:  lodd on:
        stod 4095
        call xbsywt:
        loco str1:
nextw:  pshi
        addd c1:
        stod pstr1:
        pop
        jzer crnl:
        stod 4094
        push
        subd c255:
        jneg crnl:
        call sb:
        insp 1
        push
        call xbsywt:
        pop
        stod 4094
        call xbsywt:
        lodd pstr1:
        jump nextw:
crnl:   lodd cr:
        stod 4094
        call xbsywt:
        lodd nl:
        stod 4094
        call xbsywt:
        lodd on:
        stod 4093
bgndig: call rbsywt:
        lodd 4092
        subd numoff:
        push
nxtdig: call rbsywt:
        lodd 4092
        stod nxtchr:
        subd nl:
        jzer endnum:
        mult 10
        lodd nxtchr:
        subd numoff:
        addl 0
        stol 0
        jump nxtdig:
endnum: lodd numptr:
        popi
        addd c1:
        stod numptr:
        lodd numcnt:
        jzer addnms:
        subd c1:
        stod numcnt:
        jump start:
addnms: lodd binum1:	;simple adding two numbers
        addd binum2:
        stod sum:
        jump output:
output: lodd on:	;outputs text to make it look nice and not a bunch of numbers
        stod 4095	;basically copied the method for outputting the first string
        call xbsywt:
        loco str2:
output2: pshi
        addd c1:
        stod pstr2:
        pop
        jzer crnl2:
        stod 4094
        push
        subd c255:
        jneg crnl2:
        call sb:
        insp 1
        push
        call xbsywt:
        pop
        stod 4094
        call xbsywt:
        lodd pstr2:
        jump output2:
crnl2:  lodd cr:
        stod 4094
        call xbsywt:
        lodd nl:
        stod 4094
        call xbsywt:
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
over:   lodd on:	;basically copying the method for the first string again
        stod 4095	;to output the overflow error
        call xbsywt:
        loco str3:
over2:  pshi
        addd c1:
        stod pstr3:
        pop
        jzer end:
        stod 4094
        push
        subd c255:
        jneg end:
        call sb:
        insp 1
        push
        call xbsywt:
        pop
        stod 4094
        call xbsywt:
        lodd pstr3:
        jump over2:
xbsywt: lodd 4095
        subd mask:
        jneg xbsywt:
        retn
rbsywt: lodd 4093
        subd mask:
        jneg rbsywt:
        retn
sb:     loco 8
loop1:  jzer finish:
        subd c1:
        stod lpcnt:
        lodl 1
        jneg add1:
        addl 1
        stol 1
        lodd lpcnt:
        jump loop1:
add1:   addl 1
        addd c1:
        stol 1
        lodd lpcnt:
        jump loop1:
finish: lodl 1
        retn
end:    halt
numoff: 48
nxtchr: 0
numptr: binum1:
binum1: 0
binum2: 0
lpcnt:  0
mask:   10
on:     8
nl:     10
cr:     13
c1:     1
c10:    10
c255:   255
temp:   0
sum:    0
digits: 0
numcnt: 1
pstr1:  0
pstr2:  0
pstr3:  0
a:	0
b:	0
c:	0
str1:   "Please enter a 1-5 digit number followed by enter"
str2:   "The sum of these integers is:"
str3:   "Overflow, no sum possible"