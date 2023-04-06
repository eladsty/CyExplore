 #	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = hashtable.o  hashtable_test.o


TARGET = hashtable.out


OBJDIR := /home/elad/elad.shem-tov/ds
SRCDIR := $(OBJDIR)/src/hashtable
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/hashtable

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/hashtable.h -L$(INCDIR)/stack.h
 
hashtable_test.o: $(TESDIR)/hashtable_test.c $(INCDIR)/hashtable.h $(INCDIR)/stack.h 
	cc $(CFLAGS) -c $< -o $@ 

hashtable.o: $(SRCDIR)/hashtable.c $(INCDIR)/hashtable.h  $(INCDIR)/stack.h 
	cc $(CFLAGS) -c $< -o $@ 


libhashtable.a: hashtable.o $(INCDIR)/hashtable.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libhashtable.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/hashtable.c &
	gedit $(INCDIR)/hashtable.h &
	gedit $(TESDIR)/hashtable_test.c & 

.PHONY : touch
touch: 
	touch hashtable.o 
	touch main.o 
	echo "touch to renew"

