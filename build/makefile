# Compiler being used
CC = g++

# Output directory
OUT_DIR= ../bin/

# Convert all source files to object files
OBJECTS = $(SRC:%.cpp=%.o)

# Source directory
SRC_DIR=../src

# Find all source files
SRC= $(shell find $(SRC_DIR) -name *.cpp)

# Executable name
EXE_NAME = Iceberg3D

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS=$(shell sdl2-config --cflags)

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS=$(shell sdl2-config --libs)

# Compiler flags
COMPILER_FLAGS = -w -std=c++11

# Linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lGL -lGLEW -lassimp

# Target
all: $(EXE_NAME)

$(EXE_NAME): $(OBJECTS)
	mkdir -p $(OUT_DIR) \
	&& $(CC) $(OBJECTS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUT_DIR)$(EXE_NAME) \
	&& make clean

%.o: %.cpp
	g++ -c $(COMPILER_FLAGS) $(INCLUDE_PATHS)  $< -o $@

clean:
	-rm $(SRC_DIR)/*.o
	-rm $(SRC_DIR)/core/*.o
	-rm $(SRC_DIR)/program_states/*.o
