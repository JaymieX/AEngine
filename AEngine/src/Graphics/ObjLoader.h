#pragma once

using namespace glm;
class ObjLoader {
public:
	/// C11 precautions 
	ObjLoader(const ObjLoader&) = delete;  /// Copy constructor
	ObjLoader(ObjLoader&&) = delete;       /// Move constructor
	ObjLoader& operator=(const ObjLoader&) = delete; /// Copy operator
	ObjLoader& operator=(ObjLoader&&) = delete;      /// Move operator

	static std::vector<vec3> vertices;
	static std::vector<vec2> uvCoords;
	static std::vector<vec3> normals;
	static bool loadOBJ(const char* path);

};