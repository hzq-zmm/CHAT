LIB_PATH=../jsoncpp/lib
INCLUDE=../jsoncpp/include
FLAG=-lpthread -lncurses -ljsoncpp  

app:Clientmain.o Window.o dataType.o JsonApi.o
	g++ Clientmain.o Window.o dataType.o JsonApi.o -o app -L$(LIB_PATH) -I$(INCLUDE) $(FLAG) 


Clientmain.o:Clientmain.cpp
	g++ -c Clientmain.cpp -g

Window.o:Window.cpp
	g++ -c Window.cpp -g

dataType.o:dataType.cpp
	g++ -c dataType.cpp -g

JsonApi.o:JsonApi.cpp
	g++ -c JsonApi.cpp -g

clean:
	rm -rf *.o
