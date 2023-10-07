#pragma once
#define FREEIMAGE_LIB 

#include <FreeImage.h>
#include <GL/glew.h>

#include <vector>

#include <thread>
#include <fstream>
#include <glm/glm.hpp>



struct markedThread
{


	bool isActve = false;
	std::thread t_thread;

};

struct storedPixels
{
	BYTE * m_data;
	int id;
};

namespace Feintgine
{

	class F_ScreenCapture
	{
	public:
		F_ScreenCapture();
		~F_ScreenCapture();

		static F_ScreenCapture *Instance()
		{
			if (p_Instance == 0)
			{
				p_Instance = new F_ScreenCapture;
				return p_Instance;
			}
			return p_Instance;
		}

		void init();
		void captureScreen( int width, int height );

		void saveData();

		void manualSave();


	private:


		BYTE* m_pixels; 
		int threadCounter = 0;
		int pixelIDCounter = 0;

		glm::ivec2 captureSize;

		std::vector<std::thread> m_saveThreads;
		int m_internalCount = 0;
		std::vector<FIBITMAP *> m_imageBuffers;

		std::vector<FIBITMAP *> m_copyBuffers;

		std::vector<BYTE *> m_storedPixels;

		std::vector<storedPixels> m_structPixels;


		static F_ScreenCapture *p_Instance;

	};
}


