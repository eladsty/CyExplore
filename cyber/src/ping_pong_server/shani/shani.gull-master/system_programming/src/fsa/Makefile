
# WS #
WS = fsa
# compiler flags
GD = -ansi -pedantic-errors -Wall -Wextra -g
GC = -ansi -pedantic-errors -Wall -Wextra -g -DNDEBUG -O3

# resources
OBJDIR := /home/shani/shani.gull/system_programming
SRCDIR := $(OBJDIR)/src/$(WS)
INCDIR := $(OBJDIR)/include/$(WS)
TARGETDIR := $(OBJDIR)/bin/debug
TESTDIR := $(OBJDIR)/test/$(WS)
SRCEXT := c
OBJEXT := o
INCEXT := h

# variables
TARGET = $(WS).out
objects = $(WS)_test.o $(WS).o
LIB = stcak.ar


# default make
all : release debug

$(TARGETDIR)/$(TARGET) : $(objects)
	cc $(GD) -o $@ $^
		
$(WS)_test.o : $(TESTDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(GD) -c $< -o $@
	
$(WS).o : $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(GD) -c $< -o $@
	
debug : $(objects)
	cc $(GC) $(objects) -o $(TARGET) 
release : $(objects)
	cc $(GD) $(objects) -o $(TARGET)   
clean :
	rm $(TARGET) $(objects) $(LIB)
libfoo.ar : $(object) $(TARGET)
	ar rcs $@ $^
open : 
	gedit $(TESTDIR)/*.$(SRCEXT) $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT) & 
run :
	$(TARGETDIR)/$(TARGET)

