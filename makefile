
#	gd / gc infinity flags
DEBUG = -ansi -pedantic-errors -Wall -Wextra -g
RELEASE = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

CFLAGS = $(DEBUG) -I$(INCDIR)
CPPFLAGS = 

OBJS = $(TARGET).o $(TARGET)_test.o


TARGET = vpn
PROJECTDIR := cyber


OBJDIR := ~/elad.shem-tov/$(PROJECTDIR)
SRCDIR := $(OBJDIR)/src/$(TARGET)
INCDIR := $(OBJDIR)/include
TESDIR := $(OBJDIR)/test/$(TARGET)

.PHONY: clean all

$(TARGET): $(OBJS) 
	cc $(CFLAGS) $(OBJS) -o $(TARGET) -L$(INCDIR)/$(TARGET).h

all: $(TARGET) lib$(TARGET).a 
	cc $(DEBUG) $(TARGET)_test.c $^ -o $(TARGET) -L$(INCDIR)/$(TARGET).h -I$(TARGET).ar

$(TARGET)_test.o: $(TESDIR)/$(TARGET)_test.c $(INCDIR)/$(TARGET).h
	cc $(CFLAGS) -c $< -o $@ 

$(TARGET).o: $(SRCDIR)/$(TARGET).c $(INCDIR)/$(TARGET).h
	cc $(CFLAGS) -c $< -o $@ 


lib$(TARGET).a: $(TARGET).o $(INCDIR)/$(TARGET).h
	ar rcs $@ $^
	rm -f $(OBJS)
	

.PHONY : clean
clean:
	rm -f $(OBJS)
.PHONY : cleanll
cleanll:
	rm -f $(OBJS) $(TARGET) lib$(TARGET).a
	
debug: $(OBJS)
	gcc $(DEBUG) $(OBJS) -o $(TARGET)
		
release: $(OBJS)
	gcc $(RELEASE) $(OBJS) -o $@

git:
	git add .
	git commit -m "$(TARGET)"
	git push

vlg:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)
	
vlgdb:
	valgrind -q --vgdb-error=0 ./$(TARGET)

.PHONY : open
open: 
	code $(SRCDIR)/$(TARGET).c &
	code $(INCDIR)/$(TARGET).h &
	code $(TESDIR)/$(TARGET)_test.c & 
	code $(SRCDIR)/makefile
	
start:
	mkdir $(TESDIR)
	mkdir $(SRCDIR)
	code $(SRCDIR)/$(TARGET).c &
	code $(INCDIR)/$(TARGET).h &
	code $(TESDIR)/$(TARGET)_test.c & 
	cp ~/git/makefile $(SRCDIR)/makefile
	code $(SRCDIR)/makefile

remove:
	rm -R $(TESDIR)
	rm -R $(SRCDIR)
copy:
	cp ~/git/makefile $(SRCDIR)

.PHONY : touch
touch: 
	touch $(TARGET).o 
	touch main.o 
	echo "every one was touched :)"
