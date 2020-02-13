

	AREA STACK_OP, CODE, READONLY
	EXPORT do_stack_operations
		
do_stack_operations
	;Populate R0, R1, R2 registers
	MOV R0,#0x11
	MOV R1,#0x22
	MOV R2,#0x33
	
	;Push Register contents into MSP
	PUSH {R0-R2}
	
	;Change stack pointer to PSP
	MRS R0, CONTROL
	ORR R0,R0,#0x02
	MSR CONTROL,R0
	
	;Initialize PSP with MSP value
	MRS R0,MSP
	MSR PSP,R0
	
	;Pop the register contents from PSP
	POP {R0-R2}
	
	;Return to main()
	BX LR
	END
		