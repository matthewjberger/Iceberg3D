#ifndef GLOBALINCLUDES_H
#define GLOBALINCLUDES_H

// GLAD and GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

// Boxer
#include <boxer/boxer.h>

// Bullet
#include <btBulletDynamicsCommon.h>

// STL
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <memory>

// Library Definitions
#include "Defines.h"

#endif