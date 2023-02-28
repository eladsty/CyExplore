 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = vector.o vector_test.o


TARGET = vector.out


OBJDIR := /home/el/elad.shem-tov/ds
SRCDIR := $(OBJDIR)/src/vector
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/vector

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/vector.h
 
vector_test.o: $(TESDIR)/vector_test.c $(INCDIR)/vector.h
	cc $(CFLAGS) -c $< -o $@ 

vector.o: $(SRCDIR)/vector.c $(INCDIR)/vector.h
	cc $(CFLAGS) -c $< -o $@ 


libvector.a: vector.o $(INCDIR)/vector.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libvector.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/vector.c &
	gedit $(INCDIR)/vector.h &
	gedit $(TESDIR)/vector_test.c & 

.PHONY : touch
touch: 
	touch vector.o 
	touch main.o 
	echo "touch to renew"

