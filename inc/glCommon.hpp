#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <assert.h>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <string>

#include <utility>

using std::pair;

using std::string;

using std::unique_ptr;
using std::make_unique;

using std::shared_ptr;
using std::make_shared;

using namespace glm;
using std::vector;

#ifndef pi
#define pi 3.1415926535f
#endif

#ifndef glCheckError

GLenum glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__) 

#endif