OBJS	= Decode.o Instruction.o ITypeInstruction.o JTypeInstruction.o RTypeInstruction.o main.o
SOURCE	= Decode.cpp Instruction.cpp ITypeInstruction.cpp JTypeInstruction.cpp RTypeInstruction.cpp main.cpp
HEADER	= Decode.h Instruction.h ITypeInstruction.h JTypeInstruction.h RTypeInstruction.h
OUT		= a.exe
LFLAGS	= 
CC		= g++
all: a.exe

a.exe: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) -c -o $@ $< $(LFLAGS)

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)