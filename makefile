assembler: assembler.o LinkedList.o Macro_Handler.o Text_utils.o  Assembler_Pass.o cmd_handler.o asm_utils.o File_utils.o
	gcc -g -Wall -ansi -pedantic -std=c90 assembler.o LinkedList.o  Macro_Handler.o Text_utils.o Assembler_Pass.o cmd_handler.o asm_utils.o File_utils.o -o assembler -lm
	
assembler.o: assembler.c assembler.h File_utils.o
	gcc -c -Wall -ansi -pedantic -std=c90 assembler.c -o assembler.o
		
LinkedList.o: LinkedList.c LinkedList.h
	gcc -c -Wall -ansi -pedantic -std=c90 LinkedList.c -o LinkedList.o -lm
	
Macro_Handler.o: Macro_Handler.c Macro_Handler.h LinkedList.o File_utils.o
	gcc -c -Wall -ansi -pedantic -std=c90 Macro_Handler.c -o Macro_Handler.o -lm
	
Text_utils.o: Text_utils.c Text_utils.h 
	gcc -c -Wall -ansi -pedantic -std=c90 Text_utils.c -o Text_utils.o -lm
	
	
Assembler_Pass.o: Assembler_Pass.c Assembler_Pass.h  Text_utils.o asm_utils.o cmd_handler.o
	gcc -c -Wall -ansi -pedantic -std=c90 Assembler_Pass.c -o Assembler_Pass.o -lm
	
cmd_handler.o: cmd_handler.c cmd_handler.h Text_utils.o asm_utils.o
	gcc -c -Wall -ansi -pedantic -std=c90 cmd_handler.c -o cmd_handler.o -lm
	
asm_utils.o: asm_utils.c asm_utils.h Text_utils.o LinkedList.o
	gcc -c -Wall -ansi -pedantic -std=c90 asm_utils.c -o asm_utils.o -lm
	
File_utils.o: File_utils.c File_utils.h Text_utils.o
	gcc -c -Wall -ansi -pedantic -std=c90 File_utils.c -o File_utils.o -lm	
