
# WS #
WS = prod_cons
# compiler flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g 
GD =  
GC =  -DNDEBUG 
LIB = -pthread -L. -lslist -lcbuff

# resources
WRKDIR := /home/shani/shani.gull/system_programming
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
	cc $(CFLAGS) $(GC) -o $@ $^ $(LIB)
	
$(DBGDIR)/$(TARGET) : $(OBJREL)
	cc $(CFLAGS) $(GD) -o $@ $^ $(LIB)




$(WS)_test.o : $(TESTDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT) 
	cc $(CFLAGS) -c $< -o $@ $(LIB)
	
$(WS).o : $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT) 
	cc $(CFLAGS) -c $< -o $@ $(LIB)



run :
	sudo perf stat $(DBGDIR)/$(TARGET)
db : 
	cgdb $(DBGDIR)/$(TARGET)
vlg :
	valgrind --tool=helgrind $(DBGDIR)/$(TARGET)
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


