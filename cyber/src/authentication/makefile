 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = authentication.o authentication_test.o


TARGET = authentication.out
 

OBJDIR := /home/elad/elad.shem-tov/cyber
SRCDIR := $(OBJDIR)/src/authentication
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/authentication

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/authentication.h -lcrypt
 
authentication_test.o: $(TESDIR)/authentication_test.c $(INCDIR)/authentication.h
	cc $(CFLAGS) -c $< -o $@ 

authentication.o: $(SRCDIR)/authentication.c $(INCDIR)/authentication.h
	cc $(CFLAGS) -c $< -o $@ 


libauthentication.a: authentication.o $(INCDIR)/authentication.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libauthentication.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/authentication.c &
	gedit $(INCDIR)/authentication.h &
	gedit $(TESDIR)/authentication_test.c & 

.PHONY : touch
touch: 
	touch authentication.o 
	touch main.o 
	echo "touch to renew"

