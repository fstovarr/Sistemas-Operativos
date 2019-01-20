CC=gcc

PETSFOLDER=medicalrecords
EXECUTABLE=DogProgram

EXECUTABLEDIR := bin
SOURCEDIR := src
OBJDIR := obj

SOURCES := $(wildcard $(SOURCEDIR)/*.c)
OBJECTS := $(SOURCES:$(SOURCEDIR)/%.c=$(OBJDIR)/%.o)

.PHONY: all prepare clean

all: prepare $(EXECUTABLE)

prepare:
	-@mkdir $(EXECUTABLEDIR)
	-@mkdir $(PETSFOLDER)

$(OBJECTS): $(OBJDIR)/%.o: $(SOURCEDIR)/%.c | $(OBJDIR)
	$(CC) -c $< -o $@

$(OBJDIR):
	-@mkdir $(OBJDIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLEDIR)/$(EXECUTABLE) $^

clean:
	-rm -R $(PETSFOLDER)
	-rm -R $(OBJDIR)
	-rm *.dat 