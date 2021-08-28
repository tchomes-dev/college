LOOP:   
    LODD PasCnt:  		
	JZER DONE:		
	SUBD c1:
	STOD PasCnt:		

P1:	
    LODD daddr:		
	PSHI			
	ADDD c1:
	STOD daddr:		 
	CALL FIB:		
	INSP 1			
P2:	
    PUSH			
	LODD faddr:		
	POPI			
	ADDD c1:
	STOD faddr:		
	JUMP LOOP:		
FIB:	
    LODL 1            ;load n off stack will be sp[4]
    DESP 3            ;[1]: f(n-1) [2]: f(n-2) [3]: f(n)
    JZER FIBZER:      ;if base-case 0, jump to fibzero
    SUBD c1:          ;load n-1
    JZER FIBONE:      ;if base-case 1, jump to fibone
    STOL 0            ;push n-1 for smaller caller
    CALL FIB:         ;smaller caller
    STOL 1            ;store f(n-1)
    LODL 4            ;load n
    SUBD c1:          ;
    SUBD c1:          ;subtract 2
    STOL 0            ;push n-2 for smaller caller
    CALL FIB:         ;smaller caller on (n-2)
    STOL 2            ;store f(n-2)
    ADDL 1            ;ac = f(n-1) + f(n-2)
    INSP 3            ;fix 
    RETN              ;store result
RTN:	
    LODD tmp:		
	RETN
FIBZER:	
    LODD c0:
	RETN			
FIBONE:	
    LODD c1:
	RETN			
DONE:	HALT	 
.LOC 	100			
d0:  	3			
     	9
     	18
     	23
     	25
f0:  	0			
     	0
     	0
     	0 
     	0
daddr:  d0:			
faddr:  f0:			
c0: 	0			
c1: 	1
PasCnt: 5			
LpCnt:	0			
tmp:	0			
fm1:	0			
fm2:	0			