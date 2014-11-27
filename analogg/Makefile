CC = g++
CFLAGS = -I../Base/src -I../EtherCAT/src -std=c++11 -c -Wall
LDFLAGS = -L../Base -L../EtherCAT -lLBase -lLEtherCAT -lethercat
TARGET = analogg

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(LDFLAGS) main.o -o $(TARGET)
	
main.o: main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) main.cpp
