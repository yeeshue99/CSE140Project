OBJS	= Decode.o Instruction.o I_Type.o J_Type.o R_Type.o main.o
SOURCE	= Decode.cpp Instruction.cpp I_Type.cpp J_Type.cpp R_Type.cpp main.cpp
HEADER	= Decode.h Instruction.h I_Type.h J_Type.h R_Type.h
OUT		= a.exe
CXXFLAGS	= -g -Wall -std=c++17
CXX		= g++
all: a.exe

a.exe: $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^ $(CXXFLAGS)

%.o: %.c $(HEADER)
	$(CXX) $(CFLAGS) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)