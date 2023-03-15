 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = fsa.o fsa_test.o


TARGET = fsa.out


OBJDIR := /home/el/elad.shem-tov/system_programming
SRCDIR := $(OBJDIR)/src/fsa
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/fsa

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/fsa.h
 
fsa_test.o: $(TESDIR)/fsa_test.c $(INCDIR)/fsa.h
	cc $(CFLAGS) -c $< -o $@ 

fsa.o: $(SRCDIR)/fsa.c $(INCDIR)/fsa.h
	cc $(CFLAGS) -c $< -o $@ 


libfsa.a: fsa.o $(INCDIR)/fsa.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libfsa.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/fsa.c &
	gedit $(INCDIR)/fsa.h &
	gedit $(TESDIR)/fsa_test.c & 

.PHONY : touch
touch: 
	touch fsa.o 
	touch main.o 
	echo "touch to renew"

