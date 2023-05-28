# STACK #

# compiler flags
GD = -ansi -pedantic-errors -Wall -Wextra -g
GC = -ansi -pedantic-errors -Wall -Wextra -g -DNDEBUG -O3

# resources
OBJDIR := /home/shani/shani.gull/ds
SRCDIR := $(OBJDIR)/src/stack
INCDIR := $(OBJDIR)/include/stack
TARGETDIR := $(OBJDIR)/bin/debug
TESTDIR := $(OBJDIR)/test/stack
SRCEXT := c
OBJEXT := o
INCEXT := h

# variables
TARGET = stack.out
objects = stack_test.o stack.o
LIB = stcak.ar


# default make
all : release debug

&(TARGETDIR)/$(TARGET) : $(objects)
	cc $(GD) -o $@ $^
		
stack_test.o : $(TESTDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(GD) -c $< -o $@
	
stack.o : $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(GD) -c $< -o $@
	
debug : $(objects)
	cc $(GC) $(objects) -o $(TARGET) 
release : $(objects)
	cc $(GD) $(objects) -o $(TARGET)   
clean :
	rm $(TARGET) $(objects) $(LIB)
libfoo.ar: $(object) $(TARGET)
	ar rcs $@ $^
