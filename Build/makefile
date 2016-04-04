###########################################################
# Makefile Settings                                       #
###########################################################

# Suppress output except for errors and warnings
.SILENT:

# Executable name
EXE_NAME = Iceberg3D

# Compiler being used
CC = g++

# Output directory
OUT_DIR= ../Bin/

# Source directory
SRC_DIR = ../Source

# Resources/Assets
RESOURCES = ../Source/Resources/*

# Find all source files
SRC = $(shell find $(SRC_DIR) -name '*.cpp')

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = $(shell sdl2-config --cflags) -I/usr/include/bullet

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = $(shell sdl2-config --libs)

# Convert all source files to object files
OBJECTS = $(SRC:%.cpp=%.o)

# Compiler flags
COMPILER_FLAGS = -Wall -std=c++14

# Linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lGL -lGLEW \
			   -lassimp -lBulletDynamics -lBulletSoftBody -lBulletCollision \
			   -lLinearMath

###########################################################
# Build System                                            #
###########################################################
all: $(EXE_NAME)

# Build executable from object files
$(EXE_NAME): $(OBJECTS)
	mkdir -p $(OUT_DIR) \
	&& $(CC) $(OBJECTS) $(LINKER_FLAGS) -o $(OUT_DIR)$(EXE_NAME) \
	&& cp -r $(RESOURCES) $(OUT_DIR)

# Create object files from source files
%.o: %.cpp
	$(CC) -c $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $< -o $@

# Remove all object files
clean: $(OBJECTS)
	-rm $(OBJECTS)
