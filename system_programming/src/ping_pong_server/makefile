 
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = ping_pong_server.o ping_pong_server_test.o


TARGET = ping_pong_server.out


OBJDIR := /home/elad/elad.shem-tov/system_programming
SRCDIR := $(OBJDIR)/src/ping_pong_server
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/ping_pong_server

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/ping_pong_server.h
 
ping_pong_server_test.o: $(TESDIR)/ping_pong_server_test.c $(INCDIR)/ping_pong_server.h
	cc $(CFLAGS) -c $< -o $@ 

ping_pong_server.o: $(SRCDIR)/ping_pong_server.c $(INCDIR)/ping_pong_server.h
	cc $(CFLAGS) -c $< -o $@ 


libping_pong_server.a: ping_pong_server.o $(INCDIR)/ping_pong_server.h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) libping_pong_server.a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $(TARGET)	
	
vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

.PHONY : open
open: 
	gedit $(SRCDIR)/ping_pong_server.c &
	gedit $(INCDIR)/ping_pong_server.h &
	gedit $(TESDIR)/ping_pong_server_test.c & 

.PHONY : touch
touch: 
	touch ping_pong_server.o 
	touch main.o 
	echo "touch to renew"

