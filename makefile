# Files to compile
OBJS = Main.cpp CCamera.cpp CIntroState.cpp CoreGame.cpp CShaderProgram.cpp CShader.cpp CTexture.cpp CVBO.cpp Globals.cpp

# Executable name
OBJ_NAME = vimTest

# Compiler being used
CC = g++ -std=c++11

# Compiler flags
COMPILER_FLAGS = -w 

# Linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lGL -lGLEW -lGLU -lglut

# Target
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
