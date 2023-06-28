 #	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = bst.o  bst_test.o


TARGET = bst.out


OBJDIR := /home/elad/elad.shem-tov/ds
SRCDIR := $(OBJDIR)/src/bst
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/bst

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/bst.h -L$(INCDIR)/stack.h
 
bst_test.o: $(TESDIR)/bst_test.c $(INCDIR)/bst.h $(INCDIR)/stack.h 
	cc $(CFLAGS) -c $< -o $@ 

bst.o: $(SRCDIR)/bst.c $(INCDIR)/bst.h  $(INCDIR)/stack.h 
	cc $(CFLAGS) -c $< -o $@ 


libbst.a: bst.o $(INCDIR)/bst.h
	ar rcs $@ $^
	rm -f $(OBJS)


.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libbst.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/bst.c &
	gedit $(INCDIR)/bst.h &
	gedit $(TESDIR)/bst_test.c & 

.PHONY : touch
touch: 
	touch bst.o 
	touch main.o 
	echo "touch to renew"

