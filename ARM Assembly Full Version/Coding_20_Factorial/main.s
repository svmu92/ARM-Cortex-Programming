

		AREA	myCode, CODE, READONLY
		ENTRY
		EXPORT __main
			
__main

		MOV 	R2,#5
		MOV		R1,#1
;LOOP		
		;CMP 	R2,#0
		;BEQ		DONE
		;MUL		R1,R1,R2
		;SUB		R2,R2,#1
		;B		LOOP
LOOP
		CMP		R2,#0
		ITTT	GT
		MULGT		R1,R1,R2
		SUBGT		R2,R2,#1
		BGT		LOOP

DONE	B	DONE
		END
			