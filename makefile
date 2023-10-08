CFLAG = -c
CPP = g++
OFLAG = -o
GFLAG = 

alt: my_prog

main.o: main.cpp 
	$(CPP) $(CFLAG) -s $(GFLAG) main.cpp

body.o: body.cpp
	$(CPP) $(CFLAG) $(GFLAG) body.cpp

class.o: class.cpp
	$(CPP) $(CFLAG) $(GFLAG) class.cpp

my_prog: main.o body.o class.o
	$(CPP) main.o body.o class.o $(OFLAG) my_prog

clean: 
	rm -rf *.o my_prog