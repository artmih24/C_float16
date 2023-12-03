ifeq ($(OS),Windows_NT) 
RM = del /Q /F
CP = copy /Y
EXE = a.exe
ifdef ComSpec
SHELL := $(ComSpec)
endif
ifdef COMSPEC
SHELL := $(COMSPEC)
endif
else
RM = rm -rf
CP = cp -f
EXE = a.out
endif

CFLAGS = -c -Wall

all: main.o float16.o
	g++ main.o float16.o -o $(EXE)

main.o:
	g++ $(CFLAGS) float16/main.cpp

float16.o:
	gcc $(CFLAGS) float16/float16.c

clean:
	$(RM) *.o $(EXE)