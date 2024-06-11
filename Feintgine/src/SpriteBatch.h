#ifndef _SPRITEBATCH_H_
#define _SPRITEBATCH_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"


namespace Feintgine{

	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	// A glyph is a single quad. These are added via SpriteBatch::draw
	class Glyph {
	public:
		Glyph() {};
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color);
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle); // why UVmod use glm::vec4 ? because there already a function exist using glm::vec2
		
		Glyph(vector2f *quads);
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect,  float depth, const Color& color, float angle,float spec, float lightPoint);
		Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle, const glm::vec2 & angleOption);

		Glyph(const glm::vec2 & targetPos, const glm::vec2 & dim, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle);

		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;

		vector2f getVertex(int i) { return m_verticies[i % 4]; }

		vector2f *getVerticies() { return m_verticies; }

		std::vector<Edge*> getFacingEdges(vector2f);
		std::vector<Edge*> getNotFacingEdges(glm::vec2 point);

		//This should be the only way that you modify verticies (bypassing this method will screw things up)


		vector2f* getNormals() { return normals; }
		vector2f getNormal(int i) { return normals[i % 4]; }

		Edge** getEdges() { return edges; }
		Edge* getEdge(int i) { return edges[i % 4]; }

		bool isClockwise() { return clockwise; }

		void setShadow(bool value);

		bool hasShadow;


	protected:
		//Reset (or initialize) all the verticies to (0, 0)
		void resetVerticies();

		//Update everything
		void updateAll();
		//Update the clockwise variable
		void updateClockwise();
		//Update the normal vectors
		void updateNormals();
		//Update the edges
		void updateEdges();



	private:
		
		vector2f *m_verticies;
		bool clockwise;
		vector2f *normals;
		Edge *edges[4];
		glm::vec2 rotatePoint(const glm::vec2& pos, float angle);
		glm::vec2 rotatePoint(const glm::vec2& pos, float angle, const glm::vec2 & edge);
	};

	// Each render batch is used for a single draw call
	class RenderBatch {
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
			numVertices(NumVertices), texture(Texture) {
		}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	// The SpriteBatch class is a more efficient way of drawing sprites
	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		// Initializes the spritebatch
		void init();

		// Begins the spritebatch
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

		// Ends the spritebatch
		void end();

		// Adds a glyph to the spritebatch
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
		// Adds a glyph to the spritebatch with rotation
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, float angle);
		
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, float angle,const glm::vec2 & option);
		// Adds a glyph to the spritebatch with rotation
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, const glm::vec2& dir);

		// draw shadow
		void draw(vector2f *quads);

		// draw non-Center
		void draw(const glm::vec2 & targetPos, const glm::vec2 & dim, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle);

		

		int getNumVerTices();

	//	std::vector<Edge*> getFacingEdges(vector2f point);

		std::vector<Glyph> getGlyphs() const { return _glyphs; }
		// Renders the entire SpriteBatch to the screen
		void renderBatch();
		

		void setMipMap(bool value);
	private:
		// Creates all the needed RenderBatches
		void createRenderBatches();

		// Generates our VAO and VBO
		void createVertexArray();

		// Sorts glyphs according to _sortType
		void sortGlyphs();

		// Comparators used by sortGlyphs()
		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;

		

		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphPointers; ///< This is for sorting
		std::vector<Glyph> _glyphs; ///< These are the actual glyphs
		std::vector<RenderBatch> _renderBatches;
		
	};
}

#endif