#ifndef GLOBALS_H
#define GLOBALS_H

// Array size macro
#define SIZE(x) ((sizeof(x)/sizeof(*x)))

// SDL, OpenGL, and GLEW
#include "SDL.h"
#include "GL/glew.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "GL/glu.h"

// GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>

// Bullet
#include <btBulletDynamicsCommon.h>

// STL
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#endif
