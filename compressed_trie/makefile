CC=g++
CXXFLAGS=-I.
ODIR=obj
DEPS = container.h trie.h
OBJ = container.o main.o trie.o trie_preFixSearch.o container_searchAlgorithms.o container_userInterface.o

all: novella

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

novella: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o novella