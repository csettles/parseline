CFLAGS = -Wall -pedantic -g

parseline: parseline.o checker.o
	gcc $(CFLAGS) -o parseline $^

parseline.o: parseline.c
	gcc $(CFLAGS) -c $<

checker.o: checker.c
	gcc $(CFLAGS) -c $<

clean:
	ls -al *.o
	rm -f *.o
