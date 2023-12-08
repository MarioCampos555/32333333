ifeq ($(OS),Windows_NT)
    CC = g++
    EXT = .exe
    RM = del
    SEP = \\
else
    CC = g++
    EXT =
    RM = rm -f
    SEP = /
endif

CFLAGS = -std=c++17 -Wall -c -g -static -static-libgcc -static-libstdc++
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)$(SEP)*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)$(SEP)%.cpp=%.o)
EXECUTABLE = application$(EXT)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

%.o: $(SRC_DIR)$(SEP)%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
