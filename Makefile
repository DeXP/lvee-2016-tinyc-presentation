CC=gcc
STRIP=strip
CFLAGS=-c -Wall -std=c89 -fno-builtin -fno-stack-protector -Qn
LDFLAGS=-nostdlib
SOURCES=main.c mylibc.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=lvee16-tinyc

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	$(STRIP) $(EXECUTABLE)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)

show: $(EXECUTABLE)
	./$(EXECUTABLE)
