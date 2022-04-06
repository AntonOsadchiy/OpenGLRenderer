#pragma once
#include <glm/vec3.hpp>

#include "Texture.h"


struct Material
{
	Texture<GL_TEXTURE_2D> diffuse_map;
	Texture<GL_TEXTURE_2D> specular_map;
	float shininess;

};

