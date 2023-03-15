 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = dumb.o dumb_test.o


TARGET = dumb.out


OBJDIR := /home/el/elad.shem-tov/system_programming
SRCDIR := $(OBJDIR)/src/dumb
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/dumb

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/dumb.h
 
dumb_test.o: $(TESDIR)/dumb_test.c $(INCDIR)/dumb.h
	cc $(CFLAGS) -c $< -o $@ 

dumb.o: $(SRCDIR)/dumb.c $(INCDIR)/dumb.h
	cc $(CFLAGS) -c $< -o $@ 


libdumb.a: dumb.o $(INCDIR)/dumb.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libdumb.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/dumb.c &
	gedit $(INCDIR)/dumb.h &
	gedit $(TESDIR)/dumb_test.c & 

.PHONY : touch
touch: 
	touch dumb.o 
	touch main.o 
	echo "touch to renew"

