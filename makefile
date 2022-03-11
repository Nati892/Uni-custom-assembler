main: main.o File_utils.o LinkedList.o Macro_Handler.o Text_parse.o LabelCollect.o Assembler_Pass.o
	gcc -g -Wall -ansi -pedantic -std=c90 main.o File_utils.o LinkedList.o LabelCollect.o Macro_Handler.o Text_parse.o Assembler_Pass.o -o main -lm
	
main.o: main.c main.h
	gcc -c -Wall -ansi -pedantic -std=c90 main.c -o main.o
	
File_utils.o: File_utils.c File_utils.h Text_parse.h Text_parse.c
	gcc -c -Wall -ansi -pedantic -std=c90 File_utils.c -o File_utils.o -lm
	
LinkedList.o: LinkedList.c LinkedList.h
	gcc -c -Wall -ansi -pedantic -std=c90 LinkedList.c -o LinkedList.o -lm
	
Macro_Handler.o: Macro_Handler.c Macro_Handler.h LinkedList.o
	gcc -c -Wall -ansi -pedantic -std=c90 Macro_Handler.c -o Macro_Handler.o -lm
	
Text_parse.o: Text_parse.c Text_parse.h
	gcc -c -Wall -ansi -pedantic -std=c90 Text_parse.c -o Text_parse.o -lm
	
LabelCollect.o: LabelCollect.c LabelCollect.h LinkedList.o Text_parse.o
	gcc -c -Wall -ansi -pedantic -std=c90 LabelCollect.c -o LabelCollect.o -lm
	
Assembler_Pass.o: Assembler_Pass.c Assembler_Pass.h LabelCollect.o Text_parse.o
	gcc -c -Wall -ansi -pedantic -std=c90 Assembler_Pass.c -o Assembler_Pass.o -lm
