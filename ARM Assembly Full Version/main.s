
		AREA 	myCode, CODE, READONLY
		ENTRY
		EXPORT __main
		
__main
		LDR 	R0,=A
		MOV		R1,#5
		STR		R1,[R0]
		
		LDR		R0,=D
		MOV		R1,#4
		STR		R1,[R0]

Stop	B		Stop


 		AREA 	myData, DATA, READWRITE
			;Allocate the following in the SRAM
			
A		SPACE	4
			
C		SPACE	4
	
D		SPACE	4
	
			
			END
				