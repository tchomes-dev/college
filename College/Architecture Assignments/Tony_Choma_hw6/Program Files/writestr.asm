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
        jump bgndig:
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
        jump conv:
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