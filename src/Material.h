#pragma once
#include <glm/vec3.hpp>
#include <vector>

#include "Texture.h"

//
//
//struct Material
//{
//	std::vector<Texture2D> diffuse_maps;
//	std::vector<Texture2D> specular_maps;
//	float shininess;
//	
//	Material();
//	Material(std::string_view tex1, std::string_view tex2, float shine) : diffuse_maps{ Texture2D{tex1} }, specular_maps{ Texture2D{tex2} }, shininess(shine) {}
//	
//	Material(std::vector<std::string>&& diffuse, std::vector<std::string>&& specular, float shine = 32);
//
//	Material(std::vector<Texture2D>&& diffuse, std::vector<Texture2D>&& specular, float shine = 32)
//		:diffuse_maps{ std::move(diffuse) }, specular_maps{ std::move(specular) }, shininess{ shine } 
//	{ assert(diffuse.size() <= max_diffuse_maps && specular.size() <= max_specular_maps); }
//
//	Material(Material&&) = default;
//	Material& operator=(Material&&) = default;
//
//	inline const Texture2D& diffuse_map(uint32_t index = 0) const { return diffuse_maps[index]; }
//	inline const Texture2D& specular_map(uint32_t index = 0) const { return specular_maps[index]; }
//	
//
//	static constexpr uint32_t max_diffuse_maps = 16;
//	static constexpr uint32_t max_specular_maps = 16;
//
//private:
//	Material(const Material&) = delete;
//	Material& operator=(const Material&) = delete;
//};
