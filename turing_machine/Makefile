CC=g++
D= "default"
CXXFLAGS=-I.
ODIR=obj
DEPS = configuration_settings.h direction.h final_states.h initial_state.h input_alphabet.h input_string_list.h\
		states.h tape.h tape_alphabet.h transition.h transition_function.h turing_machine.h user_interface.h\
		utility.h crash.h
OBJ = configuration_settings.o final_states.o initial_state.o input_alphabet.o input_string_list.o\
		states.o tape.o tape_alphabet.o transition.o transition_function.o turing_machine.o \
		user_interface.o utility.o main.o crash.o
all: tm

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

tm: $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o tm

package:
	mkdir $(D)
	cp *.cpp *.h Makefile $(D)
	tar -czvf $(D).tgz $(D)
	rm -r $(D)