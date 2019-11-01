;Taylor Series Expansion
;4 terms (SIN(x) = x - x^3/3! + x^5/5! - x^7/7!)
;for all x in the range [0,pi/2]
;s0 - input operand and return result
;s1 - 1/3! (invfact 3)
;s2 - 1/5! (invfact 5)
;s3 - 1/7! (invfact 7)
;s4 - x*s1, then s4*s7 
;s5 - x*s2, then s5*s8
;s6 - x*s3, then s6*s9
;s7 - x^2
;s8 - x^4
;s9 - x^6

;Avoid divisions by computing 1/3!, 1/5! and 1/7! and storing in lookup table

;VALUE	EQU		1.04719

		AREA	TaylorSeries, CODE, READONLY
		ENTRY
		EXPORT __main
				
__main
		;Enable FPU Coprocessor
		LDR		R0,=0xE000ED88
		LDR		R1,[R0]
		ORR		R1,R1,#(0xF<<20)
		STR		R1,[R0]
		
		;Reset/Flush the pipeline
		DSB
		ISB
		
		VLDR.F32	S0,=1.04719
		BL		Sincalculator
		
STOP	B		STOP

Sincalculator
		VLDR.F32	S1,invfact3
		VLDR.F32	S2,invfact5
		VLDR.F32	S3,invfact7
		
		VMUL.F32	S4,S0,S1	;x*(1/3!)
		VMUL.F32	S5,S0,S2	;x*(1/5!)
		VMUL.F32	S6,S0,S3	;x*(1/7!)
		
		VMUL.F32	S7,S0,S0	;x^2
		VMUL.F32	S4,S4,S7	;(x^3)*(1/3!)
		
		VMUL.F32	S8,S7,S7	;(x^4)
		VMUL.F32	S10,S8,S5	;(x^5)*(1/5!)
		
		VMUL.F32	S9,S8,S7	;x^6
		VMUL.F32	S9,S6,S9	;(x^7)*(1/7!)
		
		VSUB.F32	S0,S0,S4
		VSUB.F32	S0,S0,S9
		VADD.F32	S0,S0,S10
		
		BX		LR
		
	

invfact3	DCD	0x3E2AAAAA	;1/3!
invfact5	DCD	0x3C088888	;1/5!
invfact7	DCD	0x39500D00	;1/7!
		
		ALIGN
		END