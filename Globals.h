#ifndef GLOBALS_H
#define GLOBALS_H

#define GLM_FORCE_RADIANS

#define FOR(q,n) for(int q=0;q<n;q++)
#define SFOR(q,s,e) for(int q=s;q<=e;q++)
#define RFOR(q,n) for(int q=n;q>=0;q--)
#define RSFOR(q,s,e) for(int q=s;q>=e;q--)

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

#endif
