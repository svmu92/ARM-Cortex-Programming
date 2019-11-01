

		AREA datalist, DATA, READONLY

SIGNEDDATA	DCB	1,3,-2,-8,-9,5,-7,-6,4
		ALIGN
	
		AREA myCode, CODE, READONLY
		ENTRY
		EXPORT __main
			
__main
		LDR		R0,=SIGNEDDATA
		MOV		R3,#9
		MOV  	R2,#0
		
loop
		LDRSB	R1,[R0]
		ADD		R2,R2,R1
		ADD		R0,R0,#1 	;byte-sized data
		SUBS	R3,R3,#1
		BNE		loop
		
STOP	B		STOP
		END