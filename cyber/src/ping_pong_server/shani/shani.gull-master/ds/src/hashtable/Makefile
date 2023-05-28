
# WS #
WS = hashtable
# compiler flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
GD =  -g
GC =  -g -DNDEBUG -O3

# resources
WRKDIR := /home/shani/shani.gull/ds
SRCDIR := $(WRKDIR)/src/$(WS)
INCDIR := $(WRKDIR)/include/$(WS)
TESTDIR := $(WRKDIR)/test/$(WS)
DBGDIR := $(WRKDIR)/bin/debug
RELDIR := $(WRKDIR)/bin/release

SRCEXT := c
OBJEXT := o
INCEXT := h

# variables
TARGET = $(WS).out
OBJREL = $(WS)_test.o $(WS).o linked_list.o


# main targets
all : release debug
debug : $(DBGDIR)$(TARGET) 
release : $(RELDIR)$(TARGET)
	
	
$(RELDIR)$(TARGET) : $(OBJREL)
	cc $(CFLAGS) $(GC) -o $@ $^ -lm
	
$(DBGDIR)$(TARGET) : $(OBJREL)
	cc $(CFLAGS) $(GD) -o $@ $^ -lm


	
$(WS)_test.o : $(TESTDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(CFLAGS) $(GD) -c $< -o $@
	
$(WS).o : $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(CFLAGS) $(GD) -c $< -o $@
linked_list.o : $(WRKDIR)/src/linked_list/linked_list.c $(WRKDIR)/include/linked_list/linked_list.h
	cc $(GD) -c $< -o $@

run : 
		$(DBGDIR)/$(DBGDIR)$(TARGET)
clean :
	rm $(objects) lib$(WS).a $(RELDIR)/$(TARGET) $(DBGDIR)/$(TARGET)
lib$(WS).a : $(SRCDIR)/*.$(OBJEXT)
	ar -rcs $@ $^
open : 
	code $(TESTDIR)/*.$(SRCEXT) $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT) & 

