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