# Compiler und Flags
CXX = g++
CXXFLAGS = `libpng-config --cflags`
LDFLAGS = `libpng-config --ldflags`

# Target und Quellcode
TARGET = get_started_pictures
SOURCES = get_started_pictures.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Standard-Target
all: $(TARGET)

# Hauptprogramm erstellen
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Object-Dateien erstellen
%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS)

# Aufräumen
clean:
	rm -f $(OBJECTS) $(TARGET)

# Programm ausführen
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run