TARGET		= libLEtherCAT.so
CC			= g++
CFLAGS		= -Wall -g -fPIC -std=c++11 -I../Base/src
LDFLAGS		= -shared -Wl,-soname=$(TARGET) -L../Base -lLBase

CPP_FILES	= $(wildcard src/*.cpp)
OBJ_FILES	= $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

all:	$(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^
	
obj/%.o: src/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $^
	
clean:
	-rm $(OBJ_FILES)
	-rm $(TARGET)