TARGET		= libLBase.so
CC			= g++
CFLAGS		= -Wall -g -fPIC -std=c++11
LDFLAGS		= -shared -Wl,-soname=$(TARGET)

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