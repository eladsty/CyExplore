 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS =  -I$(INCDIR)
CPPFLAGS = 

OBJS = parsing.o parsing_test.o

TARGET = parsing.out

OBJDIR := /home/el/elad.shem-tov/system_programming
SRCDIR := $(OBJDIR)/src/parsing
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/parsing

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/parsing.h
	
parsing_test.o: $(TESDIR)/parsing_test.c $(INCDIR)/parsing.h
	cc  -c $< -o $@ 

parsing.o: $(SRCDIR)/parsing.c $(INCDIR)/parsing.h
	cc  -c $< -o $@ 


libparsing.a: parsing.o $(INCDIR)/parsing.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libparsing.a

debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/parsing.c &
	gedit $(INCDIR)/parsing.h &
	gedit $(TESDIR)/parsing_test.c & 

.PHONY : touch
touch: 
	touch parsing.o 
	touch main.o 
	echo "touch to renew"

