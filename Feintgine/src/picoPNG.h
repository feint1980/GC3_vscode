
#ifndef _PICOPNG_H_
#define _PICOPNG_H_
#include <vector>

namespace Feintgine
{

	extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, unsigned int in_size, bool convert_to_rgba32 = true);
}

#endif