# compiler flags
GD = -ansi -pedantic-errors -Wall -Wextra -g
GC = -ansi -pedantic-errors -Wall -Wextra -g -DNDEBUG -O3

# resources
OBJDIR := /home/shani/shani.gull/utils
SRCDIR := $(OBJDIR)/src
INCDIR := $(OBJDIR)/include
TARGETDIR := $(OBJDIR)/test
SRCEXT := c
OBJEXT := o
INCEXT := h

# variables
TARGET = fooer.out
objects = main.o foo.o
LIB = libfoo.ar


# default make
all : release debug libfoo.ar

$(TARGET) : $(objects)
	cc $(GD) -o $@ $^
		
main.o : $(TARGETDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(GD) -c $< -o $@
	
foo.o : $(SRCDIR)/*.$(SRCEXT) $(INCDIR)/*.$(INCEXT)
	cc $(GD) -c $< -o $@
	
debug : $(objects)
	cc $(GC) $(objects) -o $(TARGET) 
release : $(objects)
	cc $(GD) $(objects) -o $(TARGET)   
clean :
	rm $(TARGET) $(objects) $(LIB)
libfoo.ar: $(object) $(TARGET)
	ar rcs $@ $^
