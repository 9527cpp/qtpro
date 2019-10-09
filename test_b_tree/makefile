PROGRAM = test_b_tree.exe
CC = cl.exe 
LINK = link.exe

.PHONY : all
all: $(PROGRAM)

CFLAGS =  /EHsc /DEBUG /Zi /c
LDFLAGS = /DEBUG
LIBS = 
CPP = main.cpp
OBJS = main.obj

$(OBJS): $(CPP)
	$(CC)  $(CFLAGS) $(CPP)

$(PROGRAM): $(OBJS)
	$(LINK) $(LDFLAGS) $(OBJS) $(LIBS) /out:$(PROGRAM)
		
clean:  
    del /Q *.obj
	del /Q *.pdb
	del /Q *.exe
	del /Q *.ilk