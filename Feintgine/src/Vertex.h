
#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "Vector2.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

const int COLOR_CHANNEL_HAS_R = 1;
const int COLOR_CHANNEL_HAS_G = 2;
const int COLOR_CHANNEL_HAS_B = 4;
const int COLOR_CHANNEL_HAS_A = 8;

namespace Feintgine{
	struct Position {
		float x;
		float y;
	};

	struct Color {
		Color() : r(0), g(0), b(0), a(0) { }
		Color(glm::vec4 t_color) : r(t_color.x ), g(t_color.y), b(t_color.z ), a(t_color.w )
		{}

		Color(float R, float G, float B, float A) :
			r(R/255.0f), g(G/255.0f), b(B/255.0f), a(A/255.0f) { }
		bool change(int channel, float rate, float maxVal)
		{
			bool possitive = true;
			if (maxVal < 0)
			{
				possitive = false;
			}
			bool isDone = false;
			int totalMark = channel;
			int currentMark = 0;
			if (possitive)
			{
				if (channel & COLOR_CHANNEL_HAS_R)
				{
					if (r < maxVal)
					{
						r += rate;
					}
					else
					{
						currentMark |= COLOR_CHANNEL_HAS_R;
						r = maxVal;
					}
				}
				if (channel & COLOR_CHANNEL_HAS_G)
				{

					if (g < maxVal)
					{
						g += rate;
					}
					else
					{
						currentMark |= COLOR_CHANNEL_HAS_G;
						g = maxVal;
					}
				}
				if (channel & COLOR_CHANNEL_HAS_B)
				{
					if (b < maxVal)
					{
						b += rate;
					}
					else
					{
						currentMark |= COLOR_CHANNEL_HAS_B;
						b = maxVal;
					}
				}
				if (channel & COLOR_CHANNEL_HAS_A)
				{
					if (a < maxVal)
					{
						a += rate;
					}
					else
					{
						currentMark |= COLOR_CHANNEL_HAS_A;
						a = maxVal;
					}
				}
			}
			else
			{
				if (channel & COLOR_CHANNEL_HAS_R)
				{
					if (r > maxVal)
					{
						r += rate;
					}
					else
					{
						currentMark |= COLOR_CHANNEL_HAS_R;
						r = maxVal;
					}
				}
				if (channel & COLOR_CHANNEL_HAS_G)
				{

					if (g > maxVal)
					{
						g += rate;
					}
					else
					{
						currentMark |= COLOR_CHANNEL_HAS_G;
						g = maxVal;
					}
				}
				if (channel & COLOR_CHANNEL_HAS_B)
				{
					if (b > maxVal)
					{
						b += rate;
					}
					else
					{
						currentMark |= COLOR_CHANNEL_HAS_B;
						b = maxVal;
					}
				}
				if (channel & COLOR_CHANNEL_HAS_A)
				{
					if (a > maxVal)
					{
						a += rate;
					}
					else
					{
						currentMark |= COLOR_CHANNEL_HAS_A;
						a = maxVal;
					}
				}
			}
			if (currentMark == totalMark)
			{
				isDone = true;
			}
			else
			{
				isDone = false;
			}
			return isDone;

		}

		float r;
		float g;
		float b;
		float a;
		
	};

	struct UV {
		float u;
		float v;
	};


	//The vertex definition
	struct Vertex {
		//This is the position struct. When you store a struct or class
		//inside of another struct or class, it is called composition. This is
		//layed out exactly the same in memory as if we had a float position[2],
		//but doing it this way makes more sense.
		Position position;


		//4 bytes for r g b a color.
		Color color;

		//UV texture coordinates.
		UV uv;

		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}


		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}

	};

	struct Edge {
		Edge() { p1 = vector2f(), p2 = vector2f(); }
		Edge(vector2f point_1, vector2f point_2){ p1 = point_1, p2 = point_2; }
		vector2f p1, p2;
		vector2f getMiddle() { return (p2 - p1) / 2 + p1; }

		
		
		//Position getMiddle()	{ return (p2 - p1) / 2.0f + p1; }

	};
}

#endif