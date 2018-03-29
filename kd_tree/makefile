CC=g++
CXXFLAGS=-I.
ODIR=obj
DEPS = peptides.app.h k_d_tree.h hash_table.h file.reader.h string.service.h peptide.database.h
OBJ = peptides.app.o kd_tree.o hash_table.o main.o file.reader.o string.service.o peptide.database.o

all: peptides

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

peptides: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o peptides