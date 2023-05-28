
# WS #
WS = logger
# compiler flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GD =  
GC =  -DNDEBUG -O3

# resources
WRKDIR := /home/shani/shani.gull/utils
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
	cc $(CFLAGS) $(GC) -o $@ $^
	
$(DBGDIR)/$(TARGET) : $(OBJREL)
	cc $(CFLAGS) $(GD) -o $@ $^


	
$(WS)_test.o : $(TESTDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(CFLAGS) -c $< -o $@
	
$(WS).o : $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(CFLAGS) -c $< -o $@
	

run :
	$(DBGDIR)/$(TARGET)
db : 
	cgdb $(DBGDIR)/$(TARGET)
vlg :
	valgrind --leak-check=yes --track-origins=yes $(DBGDIR)/$(TARGET)
clean :
	rm $(OBJREL) lib$(WS).a $(RELDIR)/$(TARGET) $(DBGDIR)/$(TARGET)
lib$(WS).a : $(SRCDIR)/*.$(OBJEXT)
	ar -rcs $@ $^
open : 
	code $(TESTDIR)/*.$(SRCEXT) $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT) & 
git :
	git add .
	git commit -m "$(WS)"
	git push


