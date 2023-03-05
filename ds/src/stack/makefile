 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = stack.o stack_test.o


TARGET = stack.out


OBJDIR := /home/el/elad.shem-tov/ds
SRCDIR := $(OBJDIR)/src/stack
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/stack

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/stack.h
 
stack_test.o: $(TESDIR)/stack_test.c $(INCDIR)/stack.h
	cc $(CFLAGS) -c $< -o $@ 

stack.o: $(SRCDIR)/stack.c $(INCDIR)/stack.h
	cc $(CFLAGS) -c $< -o $@ 


libstack.a: stack.o $(INCDIR)/stack.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libstack.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/stack.c &
	gedit $(INCDIR)/stack.h &
	gedit $(TESDIR)/stack_test.c & 

.PHONY : touch
touch: 
	touch stack.o 
	touch main.o 
	echo "touch to renew"

