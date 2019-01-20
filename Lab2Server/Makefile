CC=gcc

EXECUTABLE=server
PETSFOLDER=medicalrecords

EXECUTABLEDIR := bin
SOURCEDIR := src
OBJDIR := obj

SOURCES := $(wildcard $(SOURCEDIR)/*.c)
OBJECTS := $(SOURCES:$(SOURCEDIR)/%.c=$(OBJDIR)/%.o)
 
.PHONY: all prepare cleanrecords fullclean clean

all: prepare $(EXECUTABLE)

prepare:
	-@mkdir $(PETSFOLDER)
	-@mkdir $(EXECUTABLEDIR)

$(OBJECTS): $(OBJDIR)/%.o: $(SOURCEDIR)/%.c | $(OBJDIR)
	$(CC) -c $< -o $@

$(OBJDIR):
	-@mkdir $(OBJDIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLEDIR)/$(EXECUTABLE) $^

cleanrecords:
	-rm *.dat

fullclean: cleanrecords clean

clean:
	-rm -R $(PETSFOLDER)
	-rm -R $(OBJDIR)
