OBJS	= main.o Decode.o Instruction.o RTypeInstruction.o ITypeInstruction.o JTypeInstruction.o
SOURCE	= main.cpp Decode.cpp Instruction.cpp RTypeInstruction.cpp ITypeInstruction.cpp JTypeInstruction.cpp
HEADER	= Decode.h Instruction.h RTypeInstruction.h ITypeInstruction.h JTypeInstruction.h
OUT	= a.out
LFLAGS	 = 
CC		= g++ 
all: a.out

a.out: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) -c -o $@ $< $(LFLAGS)

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)