 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS =  -I$(INCDIR)
CPPFLAGS = 

OBJS = ext2.o ext2_test.o

TARGET = ext2.out

OBJDIR := /home/elad/elad.shem-tov/system_programming
SRCDIR := $(OBJDIR)/src/ext2
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/ext2
BINDIR := $(OBJDIR)/bin/ext2

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/ext2.h -L$(INCDIR)/ext2_linux.h
	
ext2_test.o: $(TESDIR)/ext2_test.c $(INCDIR)/ext2.h
	cc  -c $< -o $@ 

ext2.o: $(SRCDIR)/ext2.c $(INCDIR)/ext2.h
	cc  -c $< -o $@ 


libext2.a: ext2.o $(INCDIR)/ext2.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libext2.a

debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/ext2.c &
	gedit $(INCDIR)/ext2.h &
	gedit $(TESDIR)/ext2_test.c & 

.PHONY : touch
touch: 
	touch ext2.o 
	touch main.o 
	echo "touch to renew"

