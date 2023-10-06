#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp//scene.h>
#include <assimp/postprocess.h>

#include  "Vertex3D.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>




namespace Feintgine
{


	class Model
	{
	public:
		Model();
		~Model();
		std::vector<Texture3D> textures_loaded;
		std::vector<Mesh> meshes; 
		std::string directory;

		bool gammaCorrection;

		Model(std::string const & path, bool gamma = false) : gammaCorrection(gamma)
		{
			//loadModel
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
			// check for errors
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
			{
				std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << "\n";
				return;
			}
			// retrieve the directory path of the filepath
			directory = path.substr(0, path.find_last_of('/'));

			// process ASSIMP's root node recursively
			processNode(scene->mRootNode, scene);

		}

		void Draw(GLSLProgram &shader);
	

	private:

		void loadModel(const std::string & path);

		void processNode(aiNode *node, const aiScene *scene);



		Mesh processMesh(aiMesh *mesh, const aiScene *scene);

		std::vector<Texture3D> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

		unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = true);
	};
}

