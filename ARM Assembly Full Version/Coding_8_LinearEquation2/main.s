;P=Q+R+S
;let Q=2,R=4,S=6

		AREA	myData, DATA, READONLY, ALIGN=2

P		SPACE	4	;Reserve 4 bytes of memory
Q		DCD		2	;create Q with data 2
R		DCD		4	;create R with data 4
S		DCD		6	;create S with data 6

		AREA	myCode, CODE, READONLY, ALIGN=2
		ENTRY
		EXPORT __main
			
__main
		LDR	R1,Q
		LDR R2,R
		LDR R3,S
		ADD R0,R1,R2
		ADD R0,R0,R3
STOP	B STOP
		END
	

