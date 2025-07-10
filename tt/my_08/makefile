# Compiler und Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
DEBUG_CXXFLAGS = -ggdb3 -O0
LDFLAGS =

# Quelldateien
SOURCES = main.cpp tokenizer.cpp calc.cpp expression_tree.cpp

# Zieldateien
TARGET = calc
DEBUG_TARGET = todebug-calc

# Objektdateien
OBJECTS = $(SOURCES:.cpp=.o)
DEBUG_OBJECTS = $(SOURCES:.cpp=_debug.o)

# Standard-Ziel: Baut das normale Programm
all: $(TARGET)

# Regel zum Erstellen des normalen Programms
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Regel zum Kompilieren der normalen Objektdateien
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug-Ziel: Baut das Debug-Programm
debug: $(DEBUG_TARGET)

# Regel zum Erstellen des Debug-Programms
$(DEBUG_TARGET): $(DEBUG_OBJECTS)
	$(CXX) $(DEBUG_CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Regel zum Kompilieren der Debug-Objektdateien
%_debug.o: %.cpp
	$(CXX) $(DEBUG_CXXFLAGS) -c $< -o $@

# Aufräumen
clean:
	rm -f $(OBJECTS) $(DEBUG_OBJECTS) $(TARGET) $(DEBUG_TARGET)

# Phony-Ziele, die keine Dateien sind
.PHONY: all debug clean
