#include "SpriteBatch.h"
#include <iostream>
#include <algorithm>

namespace Feintgine {



	Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color) :
		texture(Texture),
		depth(Depth) {
	
		topLeft.color = color;
		
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		
		bottomLeft.setPosition(destRect.x, destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;
		
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	}

	Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle) :
		texture(Texture),
		depth(Depth) {
	
		glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);
		
		// Get points centered at origin
		glm::vec2 tl(-halfDims.x, halfDims.y);
		glm::vec2 bl(-halfDims.x, -halfDims.y);
		glm::vec2 br(halfDims.x, -halfDims.y);
		glm::vec2 tr(halfDims.x, halfDims.y);

		// Rotate the points
		tl = rotatePoint(tl, angle) + halfDims;
		bl = rotatePoint(bl, angle) + halfDims;
		br = rotatePoint(br, angle) + halfDims;
		tr = rotatePoint(tr, angle) + halfDims;

		topLeft.color = color;
		
		topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		
		bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		
		bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;
		
		topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		
	}
	Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle,const glm::vec2 & angleOption) :
		texture(Texture),
		depth(Depth) {

		glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

		glm::vec2 fullDims(destRect.z , destRect.w);
		// Get points centered at origin
		glm::vec2 tl(-halfDims.x, fullDims.y);
		glm::vec2 bl(-halfDims.x, -fullDims.y);
		glm::vec2 br(halfDims.x, -fullDims.y);
		glm::vec2 tr(halfDims.x, fullDims.y);

		// Rotate the points
		tl = rotatePoint(tl, angle) + halfDims;
		bl = rotatePoint(bl, angle) + halfDims;
		br = rotatePoint(br, angle) + halfDims;
		tr = rotatePoint(tr, angle) + halfDims;

		topLeft.color = color;

		topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;

		bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;

		bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;

		topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	}


	Glyph::Glyph(vector2f *quads)
	{
		Color black = Color(0, 0, 0, 0);
		topLeft.color = black;
		topLeft.setPosition(quads[0].x, quads[0].y);
	//	topLeft.setPosition(-10, 10);
		topLeft.setUV(0, 1);

		bottomLeft.color = black;
		//bottomLeft.setPosition(-10, -10);
		bottomLeft.setPosition(quads[1].x, quads[1].y);
		bottomLeft.setUV(0, 1);

		bottomRight.color = black;
	//	bottomRight.setPosition(10, -10);
		bottomRight.setPosition(quads[2].x, quads[2].y);
		bottomRight.setUV(0, 1);

		topRight.color = black;
		//topRight.setPosition(10, 10);
		topRight.setPosition(quads[3].x, quads[3].y);
		topRight.setUV(0, 1);
		
	}

	Glyph::Glyph(const glm::vec2 & targetPos, const glm::vec2 & dim,
		const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle):
		texture(Texture),
		depth(Depth)
	{

		glm::vec2 halfDims(dim.x / 2.0f, dim.y / 2.0f);

		// Get points centered at origin
		glm::vec2 tl(0, halfDims.y);
		glm::vec2 bl(0, -halfDims.y);
		glm::vec2 br(dim.x, -halfDims.y);
		glm::vec2 tr(dim.x, halfDims.y);

		// Rotate the points
		tl = rotatePoint(tl, angle) ;
		bl = rotatePoint(bl, angle) ;
		br = rotatePoint(br, angle) ;
		tr = rotatePoint(tr, angle) ;

		topLeft.color = color;

		topLeft.setPosition(targetPos.x + tl.x, targetPos.y + tl.y);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;

		bottomLeft.setPosition(targetPos.x + bl.x, targetPos.y + bl.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;

		bottomRight.setPosition(targetPos.x + br.x, targetPos.y + br.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;

		topRight.setPosition(targetPos.x + tr.x, targetPos.y + tr.y);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}

	

	std::vector<Edge*> Glyph::getNotFacingEdges(glm::vec2 point)
	{
		std::vector<Edge*> notFacing;

		vector2f p = vector2f(point.x, point.y);

		for (int i = 0; i < 4; i++) {
			vector2f towards = p - getEdge(i)->getMiddle();
			float dot = getNormal(i) * towards;
			if (dot <= 0)
				notFacing.push_back(getEdge(i));
		}

		return notFacing;
	}



	void Glyph::updateClockwise()
	{
		double sum = 0;
		for (int i = 0; i < 3; i++) {
			sum += (getVertex(i + 1).x - getVertex(i).x) * (getVertex(i + 1).y + getVertex(i).y);
		}
		clockwise = sum > 0;
	}

	void Glyph::updateNormals()
	{
		for (int i = 0; i < 4; i++) {
			vector2f diff = getVertex(i) - getVertex(i + 1);
			float temp = diff.x;
			diff.x = diff.y;
			diff.y = -temp;
			if (!isClockwise()) diff *= -1;
			normals[i] = diff.normalized();
		}
	}

	void Glyph::updateEdges()
	{
		for (int i = 0; i < 4; i++) {
			edges[i] = new Edge(getVertex(i), getVertex(i + 1));
		}

	}

	glm::vec2 Glyph::rotatePoint(const glm::vec2& pos, float angle) {
		glm::vec2 newv;
		newv.x = pos.x * cos(angle) - pos.y * sin(angle);
		newv.y = pos.x * sin(angle) + pos.y * cos(angle);
		return newv;
	}
	glm::vec2 Glyph::rotatePoint(const glm::vec2& pos, float angle , const glm::vec2 & edge) {
		glm::vec2 newv;


// 		newv.x = pos.x * cos(angle) - pos.y * sin(angle);
// 		newv.y = pos.x * sin(angle) + pos.y * cos(angle);
		


		float s = sin(angle);
		float c = cos(angle);

		// translate point back to origin:
		newv.x -= pos.x;
		newv.y -= pos.y;

		// rotate point
		float xnew = newv.x * c - newv.y * s;
		float ynew = newv.x * s + newv.y * c;

		// translate point back:
		newv.x = xnew + pos.x;
		newv.y = ynew + pos.y;
		return newv;
	}

	SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
	{

	}

	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::init() {
		createVertexArray();

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glEnable(GL_POLYGON_SMOOTH);
		//glEnable(GL_BLEND);
		//glDisable(GL_DEPTH_TEST);


		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Set antialiasing/multisampling
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POLYGON_SMOOTH);
		glDisable(GL_MULTISAMPLE);

		

		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POLYGON_SMOOTH);
		glEnable(GL_MULTISAMPLE);
	}

	void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */) {
		_sortType = sortType;
		_renderBatches.clear();

		// Makes _glpyhs.size() == 0, however it does not free internal memory.
		// So when we later call emplace_back it doesn't need to internally call new.
		_glyphs.clear();
	}

	void SpriteBatch::end() {
		// Set up all pointers for fast sorting
		_glyphPointers.resize(_glyphs.size());
		for (size_t i = 0; i < _glyphs.size(); i++) {
			_glyphPointers[i] = &_glyphs[i];
		}

		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color) {
		_glyphs.emplace_back(destRect, uvRect, texture, depth, color, 0);
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, float angle ) {
		_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, const glm::vec2& dir) {
		const glm::vec2 right(1.0f, 0.0f);
		float angle = acos(glm::dot(right, dir));
		if (dir.y < 0.0f) angle = -angle;

		_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
	}
	
	void SpriteBatch::draw(vector2f *quads)
	{
		_glyphs.emplace_back(quads);
	}



	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, float angle, const glm::vec2 & option)
	{
		_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle,option);
	}

	void SpriteBatch::draw(const glm::vec2 & targetPos, const glm::vec2 & dim, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color, float angle)
	{
		_glyphs.emplace_back(targetPos ,dim, uvRect, Texture, Depth, color, angle);
	}

	int SpriteBatch::getNumVerTices()
	{
		return _glyphs.size();
	}

	// 	std::vector<Edge*> SpriteBatch::getNotFacingEdges(vector2f point)
// 	{
// 		std::vector<Edge *> notFacing;
// 		for (int i = 0; i < _glyphs.size(); i++)
// 		{
// 			for (int j = 0; j < 4; j++)
// 			{
// 				vector2f toward = point - _glyphs[i].edges[j]->getMiddle();
// 				float dot = _glyphs[i].edges[j]->getMiddle().normalized() * toward;
// 				if (dot <= 0)
// 				{
// 					notFacing.push_back(_glyphs[i].edges[j]);
// 				}
// 			}
// 		}
// 	}

	void SpriteBatch::renderBatch() {

		// Bind our VAO. This sets up the opengl state we need, including the 
		// vertex attribute pointers and it binds the VBO
		glBindVertexArray(_vao);


		for (size_t i = 0; i < _renderBatches.size(); i++) {

				
				glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, 40, 40, GL_TRUE);
				//glGenTextures(1, &_renderBatches[i].texture);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, _renderBatches[i].texture, 0);
				glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, 40, 40);
				glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::setMipMap(bool value)
	{

// 		glGenerateMipmap(GL_TEXTURE_2D);
// 		if (value)
// 		{
// 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 		}
// 		else
// 		{
// 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 		}

	}

	void SpriteBatch::createRenderBatches() {
		// This will store all the vertices that we need to upload
		std::vector <Vertex> vertices;

		// Resize the buffer to the exact size we need so we can treat
		// it like an array
		vertices.resize(_glyphPointers.size() * 6);

		if (_glyphPointers.empty()) {
			return;
		}

		int offset = 0; // current offset
		int cv = 0; // current vertex

		//Add the first batch
		_renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);
		vertices[cv++] = _glyphPointers[0]->topLeft;
		vertices[cv++] = _glyphPointers[0]->bottomLeft;
		vertices[cv++] = _glyphPointers[0]->bottomRight;
		vertices[cv++] = _glyphPointers[0]->bottomRight;
		vertices[cv++] = _glyphPointers[0]->topRight;
		vertices[cv++] = _glyphPointers[0]->topLeft;
		offset += 6;

		//Add all the rest of the glyphs
		for (auto cg = 1; cg < _glyphPointers.size(); cg++) {

			// Check if this glyph can be part of the current batch
			if (_glyphPointers[cg]->texture != _glyphPointers[cg - 1]->texture) {
				// Make a new batch
				_renderBatches.emplace_back(offset, 6, _glyphPointers[cg]->texture);
			}
			else {
				// If its part of the current batch, just increase numVertices
				_renderBatches.back().numVertices += 6;
			}
			vertices[cv++] = _glyphPointers[cg]->topLeft;
			vertices[cv++] = _glyphPointers[cg]->bottomLeft;
			vertices[cv++] = _glyphPointers[cg]->bottomRight;
			vertices[cv++] = _glyphPointers[cg]->bottomRight;
			vertices[cv++] = _glyphPointers[cg]->topRight;
			vertices[cv++] = _glyphPointers[cg]->topLeft;
			offset += 6;
		}
		
		// Bind our VBO
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		// Orphan the buffer (for speed)
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		// Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void SpriteBatch::createVertexArray() {

		// Generate the VAO if it isn't already generated
		if (_vao == 0) {
			glGenVertexArrays(1, &_vao);
		}

		// Bind the VAO. All subsequent opengl calls will modify it's state.
		glBindVertexArray(_vao);

		//G enerate the VBO if it isn't already generated
		if (_vbo == 0) {
			glGenBuffers(1, &_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		//Tell opengl what attribute arrays we need
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		


		/* glVertexAttribPointer(Index, Count ( per vertex) , Normalize , The amount of bytes between each vertex,
			pointer to the actual atrribute )
		*/
		
		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//This is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//glVertexAttribPointer(3, 1, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex,isLight));
		//This is the Spec attribute pointer
		//glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, multiplier));

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//glEnableVertexAttribArray(3);

	}

	void SpriteBatch::sortGlyphs() {

		switch (_sortType) {
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
			break;
		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
		return (a->texture < b->texture);
	}
}