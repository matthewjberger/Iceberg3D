#ifndef GLOBALS_H
#define GLOBALS_H

#define GLM_FORCE_RADIANS

#define SIZE(x) ((sizeof(x)/sizeof(*x)))

#include "SDL.h"
#include "GL/glew.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "GL/glu.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace glm;

#endif
