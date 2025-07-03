# Compiler und Flags
CXX = g++ -std=c++17
CXXFLAGS = `libpng-config --cflags`
LDFLAGS = `libpng-config --ldflags`

# Debug Flags
DEBUG_CXXFLAGS = -ggdb3 -O0 `libpng-config --cflags`

# Target und Quellcode
TARGET = parallel_blurring
DEBUG_TARGET = parallel_blurring_debug
SOURCES = parallel_blurring.cpp
OBJECTS = $(SOURCES:.cpp=.o)
DEBUG_OBJECTS = $(SOURCES:.cpp=_debug.o)

# Standard-Target
all: $(TARGET)

# Hauptprogramm erstellen
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Debug-Version erstellen
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(DEBUG_OBJECTS)
	$(CXX) -o $(DEBUG_TARGET) $(DEBUG_OBJECTS) $(LDFLAGS)

# Object-Dateien erstellen
%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS)

# Debug Object-Dateien erstellen
%_debug.o: %.cpp
	$(CXX) -c $< $(DEBUG_CXXFLAGS) -o $@

# Aufräumen
clean:
	rm -f $(OBJECTS) $(DEBUG_OBJECTS) $(TARGET) $(DEBUG_TARGET)

# Programm ausführen
run: $(TARGET)
	./$(TARGET)

# Debug-Version ausführen
run-debug: $(DEBUG_TARGET)
	./$(DEBUG_TARGET)

# Phony targets
.PHONY: all clean run debug run-debug