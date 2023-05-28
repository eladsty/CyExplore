
# WS #
WS = authentication
# compiler flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g 
GD =  
GC = -DNDEBUG -O3

# resources
WRKDIR := /home/shani/shani.gull/cyber
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
OBJREL = $(WS)_test.o $(WS).o


# main targets
all : release debug
debug : $(DBGDIR)/$(TARGET) 
release : $(RELDIR)/$(TARGET)
	
	
$(RELDIR)/$(TARGET) : $(OBJREL)
	cc $(CFLAGS) $(GC) $^ -o $@ -lcrypt -lpam -lpam_misc
	
$(DBGDIR)/$(TARGET) : $(OBJREL)
	cc $(CFLAGS) $^ -o $@ -lcrypt -lpam -lpam_misc


	
$(WS)_test.o : $(TESTDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(CFLAGS) $(GC) -c $< -o $@ -I/usr/include/security/pam_misc.h
	
$(WS).o : $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(CFLAGS) $(GC) -c $< -o $@ 
	
db :
	cgdb $(DBGDIR)/$(TARGET)
vlg :
	valgrind --leak-check=yes --track-origins=yes $(DBGDIR)/$(TARGET)
run :
	$(DBGDIR)/$(TARGET)
clean :
	rm $(objects) lib$(WS).a $(RELDIR)/$(TARGET) $(DBGDIR)/$(TARGET)
lib : $(SRCDIR)/*.$(OBJEXT)
	ar -rcs lib$(WS).a $^
open : 
	code $(TESTDIR)/*.$(SRCEXT) $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT) & 

