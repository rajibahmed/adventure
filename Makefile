COMPILER = g++
CFLAGS = -g
SOURCES =  Element.cpp Node.cpp Player.cpp Parser.cpp  Socket.cpp main.cpp
APP = output/advent
OBJECTS = $(SOURCES:.cpp=.o)


all: $(SOURCES) $(APP)

$(APP): $(OBJECTS)
	$(COMPILER) $(CFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf *.o $(APP)

