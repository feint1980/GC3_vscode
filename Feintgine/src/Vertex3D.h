#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <glew.h>
#include "GLSLProgram.h"
#include <iostream>

#define MAX_BONE_INFLUENCE 4

namespace Feintgine
{



	struct Vertex3D
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 UV;
		glm::vec3 tangent;
		glm::vec3 bitangent;

		int m_boneIDs[MAX_BONE_INFLUENCE];
		float m_weights[MAX_BONE_INFLUENCE];

	};

	struct Texture3D
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh {
	public:
		// mesh data
		std::vector<Vertex3D>       vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture3D>      textures;

		Mesh(std::vector<Vertex3D> t_vertices, std::vector<unsigned int> t_indices, std::vector<Texture3D> t_textures)
		{
			vertices = t_vertices;
			indices = t_indices;
			textures = t_textures;

			setupMesh();
			//std::cout << "set up mesh done \n";
		}

		void Draw(GLSLProgram & shader)
		{
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			for (unsigned int i = 0; i < textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
												  // retrieve texture number (the N in diffuse_textureN)
				std::string number;
				std::string name = textures[i].type;
				if (name == "texture_diffuse")
					number = std::to_string(diffuseNr++);
				else if (name == "texture_specular")
					number = std::to_string(specularNr++);

				shader.setUniformInt(("material." + name + number).c_str(), i);
				glBindTexture(GL_TEXTURE_2D, textures[i].id);
			}
			glActiveTexture(GL_TEXTURE0);

			// draw mesh
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	private:
		//  render data
		unsigned int VAO, VBO, EBO;

		void setupMesh()
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), &vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
				&indices[0], GL_STATIC_DRAW);

			// vertex positions
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)0);
			// vertex normals
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, normal));
			// vertex texture coords
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, UV));

			glBindVertexArray(0);
		}
	};



}