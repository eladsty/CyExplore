
# WS #
WS = vsa
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
		
$(WS)_test.o : $(TESTDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(GC) -c $< -o $@
	
$(WS).o : $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(GC) -c $< -o $@
	
debug : $(WS)_test_debug.o $(WS)_debug.o 
	cc $(GD) $^ -o debug_$(TARGET) 
release : $(objects)
	cc $(GC) $(objects) -o release_$(TARGET)   


clean :
	rm $(TARGET) $(objects) $(LIB)
libfoo.ar : $(object) $(TARGET)
	ar rcs $@ $^
open : 
	gedit $(TESTDIR)/*.$(SRCEXT) $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT) & 
code : 
	code $(TESTDIR)/*.$(SRCEXT) $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT) & 
run :
	$(TARGETDIR)/$(TARGET)
$(WS)_test_debug.o : $(TESTDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(GD) -c $< -o $@
$(WS)_debug.o : $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(GD) -c $< -o $@
	
