

		AREA fact,CODE,READONLY
			ENTRY
			EXPORT __main
				
;Iterative Implementation				
;__main

;Fact
		;MOV		R0,#8
		;MOV		R1,#1
;LOOP	CMP		R0,#1
		;BLS		DONE
		
		;MUL		R1,R1,R0
		;SUB		R0,R0,#1
		;B		LOOP
	
;DONE
		;MOV		R0,R1
		;BX		LR
		
;STOP	B		STOP
		;ALIGN
		;END
			
			
;Recursive Algorithm
__main
		MOV		R0,#8

FACT	CMP		R0,#1
		BLS		DONE
		PUSH	{R0,LR}
		SUB		R0,R0,#1 ;n=n-1
		BL		FACT
		
		POP		{R1,LR}
		MUL		R0,R0,R1	;R0=n*FACT(n-1)
		BX		LR
		
DONE	
		MOV		R0,#1
		BX		LR
		
		ALIGN
		END