#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
	std::vector<AssimpTexture> textures_loaded;
	std::vector<Mesh> m_meshes;
	std::string directory;

public:
	Model(const std::string& path)
	{
		load_model(path);
	}


	const std::vector<Mesh>& meshes() const { return m_meshes; }

private:
	void load_model(const std::string& path);

	void process_node(aiNode* node, const aiScene* scene);
	Mesh process_mesh(aiMesh* mesh, const aiScene* scene);


	std::vector<AssimpTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};