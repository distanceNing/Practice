var=main.o Csocket.o check_permission.o send_file.o
client: $(var)
	g++ $(var) -o client
main.o:send_file.h check_permission.h Csocket.h
	g++ -c main.cpp 
Csocket.o: Csocket.h Csocket.cpp
	g++  -c Csocket.cpp  
check_permission.o: check_permission.h check_permission.cpp
	g++  -c check_permission.cpp
send_file.o:Csocket.h send_file.h send_file.cpp
	g++ -c send_file.cpp 
.PHONY:clean
clean:
	-rm *.o
