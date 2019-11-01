

		AREA myCode, CODE, READONLY
		ENTRY
		EXPORT __main
			
__main
		LDR 	R0,=0xE000ED88
		LDR		R1,[R0]
		ORR		R1,R1,#(0xF<<20)
		STR		R1,[R0]

		;ADRL	R1,ConstantTable
		VLDR.F	S2,C_TEN
		VLDR.F	S3,C_PIE
		VMUL.F	S4,S2,S3
		

		
		
STOP	B		STOP
		
;ConstantTable
C_ONE				DCD	0x3F800000				;1.0
C_TWO				DCD	0x40000000				;2.0
C_POINT1			DCD	0xBDCCCCCD				;-0.1
C_TEN				DCD	0x41200000				;10.0
C_HUNDRED			DCD	0x42C80000				;100.0
C_PIE				DCD	0x4048F5C3				;pi
C_E					DCD 0x402D70A4				;e
				
		END			