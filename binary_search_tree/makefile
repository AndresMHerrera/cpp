CC=g++
CXXFLAGS=-I.
ODIR=obj
DEPS = binary.search.tree.h stdin.reader.h
OBJ = binary.search.tree.o main.o stdin.reader.o

all: bst

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

bst: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o bst