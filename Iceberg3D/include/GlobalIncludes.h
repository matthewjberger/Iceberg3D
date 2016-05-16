#ifndef GLOBAL_INCLUDES_H
#define GLOBAL_INCLUDES_H

// TODO: Remove this after decoupling OpenGL rendering from logic
#include "GLHeaders.h"

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>

// Boxer
#include <boxer/boxer.h>

// Bullet
#include <btBulletDynamicsCommon.h>

// Freetype 2
#include <ft2build.h>
#include FT_FREETYPE_H

// STL
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include <map>

// Library Definitions
#include "Defines.h"

#endif