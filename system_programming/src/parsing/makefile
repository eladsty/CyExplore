 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS =  -I$(INCDIR)
CPPFLAGS = 

OBJS = vsa.o vsa_test.o

TARGET = vsa.out

OBJDIR := /home/el/elad.shem-tov/system_programming
SRCDIR := $(OBJDIR)/src/vsa
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/vsa

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/vsa.h
	
vsa_test.o: $(TESDIR)/vsa_test.c $(INCDIR)/vsa.h
	cc  -c $< -o $@ 

vsa.o: $(SRCDIR)/vsa.c $(INCDIR)/vsa.h
	cc  -c $< -o $@ 


libvsa.a: vsa.o $(INCDIR)/vsa.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libvsa.a

debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/vsa.c &
	gedit $(INCDIR)/vsa.h &
	gedit $(TESDIR)/vsa_test.c & 

.PHONY : touch
touch: 
	touch vsa.o 
	touch main.o 
	echo "touch to renew"

