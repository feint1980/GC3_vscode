#include "F_ScreenCapture.h"

#include <string>
#include <iostream>
#include <chrono>
#include <algorithm>

namespace Feintgine
{

	F_ScreenCapture *F_ScreenCapture::p_Instance = 0;

	F_ScreenCapture::F_ScreenCapture()
	{
	}


	F_ScreenCapture::~F_ScreenCapture()
	{
	}

	void F_ScreenCapture::init()
	{
		// Init 
		FreeImage_Initialise();
		captureSize = glm::ivec2(760, 718);
		
		m_pixels  = new BYTE[3 * captureSize.x * captureSize.y];
		//m_saveThread.join();
	}

	

	void F_ScreenCapture::captureScreen( int width, int height)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		
		

		//BYTE * pixels = new BYTE[3 * 768 * 768];
		glReadPixels(26, 0, captureSize.x, captureSize.y, GL_BGR, GL_UNSIGNED_BYTE, m_pixels);
		
		FIBITMAP * image = std::move(FreeImage_ConvertFromRawBits(m_pixels, captureSize.x, captureSize.y, 3 * captureSize.x,24, 0x0000FF, 0xFF0000, 0x00FF00, false));
		

	/*	storedPixels t_pixel;
		t_pixel.m_data = std::move(pixels);
		t_pixel.id = pixelIDCounter++;
		m_structPixels.push_back(t_pixel);*/
		//m_storedPixels.push_back(std::move(m_pixels));
		m_imageBuffers.emplace_back(image);
		//delete image;
		
		//delete[] pixels;
		glReadBuffer(GL_BACK);

	}

	

	void F_ScreenCapture::saveData()
	{
		//std::cout << "saveData " << m_imageBuffers.size() << "\n";
		if (m_imageBuffers.size() > 100)
		{

			m_copyBuffers = std::move(m_imageBuffers);
			m_imageBuffers.clear();
			//m_copyBuffers = m_imageBuffers;
			//std::cout << "called \n";
			m_saveThreads.emplace_back([&]()
			{

				for (int i = 0; i < m_copyBuffers.size(); i++)
				{
					std::string fileLocation = "E:/template/my_last/GC3/Feintgine/CapturedData/captured_" + std::to_string(m_internalCount++) + ".jpg";
					//std::ofstream outFile;
					//outFile.open(fileLocation);
					//outFile << "test";// m_copyBuffers[i]->data;
					//outFile.close();
					FreeImage_Save(FIF_JPEG, m_copyBuffers[i], fileLocation.c_str(), 0);
					FreeImage_Unload(m_copyBuffers[i]);	
				}
				for (auto p : m_copyBuffers)
				{
					delete p;
					//free(p);
				}

				m_copyBuffers.clear();
			});	
		}
		for (int i = 0; i < m_saveThreads.size(); i++)
		{
			if (i >= threadCounter)
			{
				m_saveThreads[i].detach();
				threadCounter++;
			}	
		}
	}

	void F_ScreenCapture::manualSave()
	{
		for (int i = 0; i < m_structPixels.size(); i++)
		{
			FIBITMAP * image = std::move(FreeImage_ConvertFromRawBits(m_structPixels[i].m_data, 768, 768, 3 * 768, 24, 0x0000FF, 0xFF0000, 0x00FF00, false));
			std::string fileLocation = "E:/template/my_last/GC3/Feintgine/CapturedData/captured_" + std::to_string(m_internalCount++) + ".jpg";
			FreeImage_Save(FIF_JPEG, image, fileLocation.c_str(), 0);
			FreeImage_Unload(image);
		}
	}

}
