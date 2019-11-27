#pragma once

#include <Windows.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
#include <utility>
#include <functional>
#include <bitset>
#include <array>
#include <ctime>
#include <ratio>
#include <chrono>

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>
#include <gtx/matrix_decompose.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define RESOURCES(path) { return "src/Resources" + path; }

constexpr float Magnitude(const glm::vec3 v){ return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);}

constexpr void Maximum(const glm::vec3& v, glm::vec3& max)
{
	max.x = v.x > max.x ? v.x : max.x;
	max.y = v.y > max.y ? v.y : max.y;
	max.z = v.z > max.z ? v.z : max.z;
}

constexpr void Minimum(const glm::vec3& v, glm::vec3& min)
{
	min.x = v.x < min.x ? v.x : min.x;
	min.y = v.y < min.y ? v.y : min.y;
	min.z = v.z < min.z ? v.z : min.z;
}

//#define XR_USE_PLATFORM_WIN32
//#define XR_USE_GRAPHICS_API_OPENGL
//#include <openxr/openxr.h>
//#include <openxr/openxr_platform.h>

