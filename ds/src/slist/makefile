 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = slist.o slist_test.o


TARGET = slist.out


OBJDIR := /home/elad/elad.shem-tov/ds
SRCDIR := $(OBJDIR)/src/slist
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/slist

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/slist.h
 
slist_test.o: $(TESDIR)/slist_test.c $(INCDIR)/slist.h
	cc $(CFLAGS) -c $< -o $@ 

slist.o: $(SRCDIR)/slist.c $(INCDIR)/slist.h
	cc $(CFLAGS) -c $< -o $@ 


libslist.a: slist.o $(INCDIR)/slist.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libslist.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/slist.c &
	gedit $(INCDIR)/slist.h &
	gedit $(TESDIR)/slist_test.c & 

.PHONY : touch
touch: 
	touch slist.o 
	touch main.o 
	echo "touch to renew"

