PROGRAM=InodeInfo
OBJECTS=InodeInfo.o
CXX = gcc
DEBUG=
LFLAGS=
CFLAGS=-Wall -pedantic -std=c11

#%.o: %.c
#	$(CXX) $(CFLAGS) -c $^

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $(PROGRAM)

clean: 
	rm *.o
	#rm *.out
	rm -rf $(PROGRAM)