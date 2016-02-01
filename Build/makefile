# Compiler being used
CC = g++

# Output directory
OUT_DIR= ../Bin/

# Convert all source files to object files
OBJECTS = $(SRC:%.cpp=%.o)

# Source directory
SRC_DIR=../Source

# Find all source files
SRC= $(shell find $(SRC_DIR) -name *.cpp)

# Executable name
EXE_NAME = Iceberg3D

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS=$(shell sdl2-config --cflags) -I/usr/include/bullet

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS=$(shell sdl2-config --libs)

# Compiler flags
COMPILER_FLAGS = -w -std=c++11

# Linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lGL -lGLEW -lassimp -lBulletDynamics -lBulletSoftBody -lBulletCollision -lLinearMath

# Target
all: $(EXE_NAME)

$(EXE_NAME): $(OBJECTS)
	mkdir -p $(OUT_DIR) \
	&& $(CC) $(OBJECTS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUT_DIR)$(EXE_NAME) \

%.o: %.cpp
	g++ -c $(COMPILER_FLAGS) $(INCLUDE_PATHS)  $< -o $@

clean: $(OBJECTS)
	-rm $(OBJECTS)
