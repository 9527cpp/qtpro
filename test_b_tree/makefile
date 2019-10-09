PROGRAM = main.exe
CC = cl.exe 
LINK = link.exe

.PHONY : all
all: $(PROGRAM)

CFLAGS = /w /EHsc /D_CRT_SECURE_NO_DEPRECATE /Zi
LDFLAGS = /DEBUG
LIBS = 

OBJS = main.obj

$(PROGRAM): $(OBJS)
	$(LINK) $(LDFLAGS) $(OBJS) $(LIBS) /out:$(PROGRAM)
		
clean:  
    del /Q *.obj
	del /Q *.pdb
	del /Q *.exe
	del /Q *.ilk