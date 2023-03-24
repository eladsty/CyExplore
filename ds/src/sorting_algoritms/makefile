 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = sorting.o sorting_test.o


TARGET = sorting.out


OBJDIR := /home/el/elad.shem-tov/ds
SRCDIR := $(OBJDIR)/src/sorting
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/sorting

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/sorting.h
 
sorting_test.o: $(TESDIR)/sorting_test.c $(INCDIR)/sorting.h
	cc $(CFLAGS) -c $< -o $@ 

sorting.o: $(SRCDIR)/sorting.c $(INCDIR)/sorting.h
	cc $(CFLAGS) -c $< -o $@ 


libsorting.a: sorting.o $(INCDIR)/sorting.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libsorting.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/sorting.c &
	gedit $(INCDIR)/sorting.h &
	gedit $(TESDIR)/sorting_test.c & 

.PHONY : touch
touch: 
	touch sorting.o 
	touch main.o 
	echo "touch to renew"

