 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = recursion.o recursion_test.o


TARGET = recursion.out


OBJDIR := /home/el/elad.shem-tov/ds
SRCDIR := $(OBJDIR)/src/recursion
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/recursion

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/recursion.h
 
recursion_test.o: $(TESDIR)/recursion_test.c $(INCDIR)/recursion.h
	cc $(CFLAGS) -c $< -o $@ 

recursion.o: $(SRCDIR)/recursion.c $(INCDIR)/recursion.h
	cc $(CFLAGS) -c $< -o $@ 


librecursion.a: recursion.o $(INCDIR)/recursion.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) librecursion.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/recursion.c &
	gedit $(INCDIR)/recursion.h &
	gedit $(TESDIR)/recursion_test.c & 

.PHONY : touch
touch: 
	touch recursion.o 
	touch main.o 
	echo "touch to renew"

