CC=g++
CXXFLAGS=-I.
ODIR=obj
DEPS = queue.h
OBJ = queue.o main.o

all: queue

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

queue: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o queue