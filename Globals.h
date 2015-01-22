#ifndef GLOBALS_H
#define GLOBALS_H

#define GLM_FORCE_RADIANS

#define PI 3.1415
#define RADIANS_TO_DEGREES(radians) float( ( (radians) * (180.0 / PI)  ) )
#define DEGREES_TO_RADIANS(angle) float( ( ( (angle) / 180.0 ) * PI) )

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_image.h"
#include "GL/glu.h"
#include "CTexture.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace glm;

extern GLuint MakeShader(string path, GLuint shaderType);
extern GLuint MakeProgram(GLuint vShaderID, GLuint fShaderID);

extern void PrintShaderLog(GLuint shader);

#endif
