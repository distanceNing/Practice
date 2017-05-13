var=main.o Csocket.o check_permission.o receive_file.o
server: $(var)
	g++ $(var) -o server
main.o:receive_file.h check_permission.h Csocket.h
	g++ -c main.cpp 
Csocket.o: Csocket.h Csocket.cpp
	g++  -c Csocket.cpp  
check_permission.o: check_permission.h check_permission.cpp
	g++  -c check_permission.cpp 
receive_file.o:Csocket.h receive_file.h receive_file.cpp
	g++ -c receive_file.cpp 
.PHONY:clean
clean:
	-rm *.o
