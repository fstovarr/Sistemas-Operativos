CC=gcc

PETSFOLDER=medicalrecords
EXECUTABLE=DogProgram

SOURCEDIR := src
OBJDIR := obj

SOURCES := $(wildcard $(SOURCEDIR)/*.c)
OBJECTS := $(SOURCES:$(SOURCEDIR)/%.c=$(OBJDIR)/%.o)

.PHONY: clean

all: prepare $(EXECUTABLE)

prepare:
	@mkdir $(PETSFOLDER)

$(OBJECTS): $(OBJDIR)/%.o: $(SOURCEDIR)/%.c | $(OBJDIR)
	$(CC) -c $< -o $@

$(OBJDIR):
	@mkdir $(OBJDIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $^

clean:
	rm -f $(EXECUTABLE)
	rm -R $(PETSFOLDER)
	rm -R $(OBJDIR)
	rm *.dat
