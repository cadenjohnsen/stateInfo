CC = g++
exe_file = stateFacts

$(exe_file): stateFacts.o runFacts.o
	$(CC) stateFacts.o runFacts.o -o $(exe_file)
state_facts.o: stateFacts.cpp
	$(CC) -c stateFacts.cpp
run_facts.o: runFacts.cpp
	$(CC) -c runFacts.cpp
clean:
	rm -f *.out *.o $(exe_file)
