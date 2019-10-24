PROGRAM = test_sort.exe
CC = cl.exe 
LINK = link.exe

.PHONY : all
all: $(PROGRAM)

CFLAGS =  /EHsc /DEBUG /Zi /c
LDFLAGS = /DEBUG
LIBS = 

OBJS = test_sort.obj 

.c.obj:
	$(CC)  $(CFLAGS) $*.c

.cpp.obj:
	$(CC)  $(CFLAGS) $*.cpp

$(PROGRAM): $(OBJS)
	$(LINK) $(LDFLAGS) $(OBJS) $(LIBS) /out:$(PROGRAM)

clean:  
    del /Q *.obj
	del /Q *.pdb
	del /Q *.exe
	del /Q *.ilk