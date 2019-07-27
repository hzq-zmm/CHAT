LIB_PATH=../jsoncpp/lib
INCLUDE=../jsoncpp/include
FLAG=-lpthread -ljsoncpp

app:servermain.o dataType.o datapool.o JsonApi.o 
	g++ servermain.o JsonApi.o dataType.o datapool.o  -o app -L$(LIB_PATH) -I$(INCLUDE) $(FLAG)

servermain.o:servermain.cpp
	g++ -c servermain.cpp 

dataType.o:dataType.cpp
	g++ -c dataType.cpp

datapool.o:datapool.cpp
	g++ -c datapool.cpp

JsonApi.o:JsonApi.cpp
	g++ -c JsonApi.cpp


clean:
	rm -rf *.o
