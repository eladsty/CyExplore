 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = comparison_sorts.o comparison_sorts_test.o


TARGET = comparison_sorts.out


OBJDIR := /home/elad/elad.shem-tov/ds
SRCDIR := $(OBJDIR)/src/comparison_sorts
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/comparison_sorts

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/comparison_sorts.h
 
comparison_sorts_test.o: $(TESDIR)/comparison_sorts_test.c $(INCDIR)/comparison_sorts.h
	cc $(CFLAGS) -c $< -o $@ 

comparison_sorts.o: $(SRCDIR)/comparison_sorts.c $(INCDIR)/comparison_sorts.h
	cc $(CFLAGS) -c $< -o $@ 


libcomparison_sorts.a: comparison_sorts.o $(INCDIR)/comparison_sorts.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libcomparison_sorts.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/comparison_sorts.c &
	gedit $(INCDIR)/comparison_sorts.h &
	gedit $(TESDIR)/comparison_sorts_test.c & 

.PHONY : touch
touch: 
	touch comparison_sorts.o 
	touch main.o 
	echo "touch to renew"

