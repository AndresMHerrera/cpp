CC=g++
CXXFLAGS=-I.
ODIR=obj
DEPS = stack.h
OBJ = stack.o main.o

all: stack

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

stack: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o stack