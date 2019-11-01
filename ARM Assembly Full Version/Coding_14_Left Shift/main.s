

		AREA leftShift,CODE,READONLY
		ENTRY
		EXPORT __main
			
__main
		MOV R0,#0x11
		LSL	R1,R0,#1 ; SHIFT 1 BIT LEFT
		LSL R2,R1,#1 
		
STOP	B	STOP
		END
		