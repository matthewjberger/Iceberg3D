# Files to compile
OBJS = *.cpp 

# Executable name
OBJ_NAME = vimTest

# Compiler being used
CC = g++ -std=c++11

# Compiler flags
COMPILER_FLAGS = -w 

# Linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lGL -lGLEW -lGLU

# Target
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
