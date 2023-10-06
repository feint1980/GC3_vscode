
#ifndef _FEINT_COMMON_H_
#define _FEINT_COMMON_H_

#include <string>
#include <glm/glm.hpp>
#include <fcntl.h>
#ifdef _WIN32 
#include <io.h>
#include <windows.h>
#elif __linux__ 

#endif

#include <locale>
#include <clocale>
#include <codecvt>
#include <iostream>
#include <SDL2/SDL.h>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include "objectData.pb.h"
#include <time.h>
#include <fstream>
#include "GUI.h"
#include <cctype>
#include <sstream>


#define RANDOM_VALUE (_type_,t_lo,t_hi) t_lo + static_cast <_type_> (rand()) / (static_cast <_type_> (RAND_MAX / (t_hi - t_lo)))

#define RAD_2_DEGREE (degreeValue) (degreeValue * 57.2957795f);
#define DEGREE_2_RAD (radValue) (degreeValue / 57.2957795);

static float radToDegree(float rad) 
{
	return rad * 57.2957795f;
}

static float degreeToRad(float deg)
{
	return deg / 57.2957795f;
}

static glm::vec2 globalRotatePoint(const glm::vec2& pos, float angle) {
	glm::vec2 newv;
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv;
}

class feint_common
{
public:
	feint_common();

	static feint_common *Instance()
	{
		if (p_Instance == 0)
		{
			p_Instance = new feint_common;
			return p_Instance;
		}
		return p_Instance;
	}

	~feint_common();

	float getRandomNum(float low, float hight);

	void testPrintUtf8(const std::wstring & msg);

	void showMessageBox(const std::string & msgtitle, const std::string & msgcontent);

	bool showConfirmationBox(const std::string & msgtitle, const std::string & msgcontent);

	inline bool isFileExist(const std::string& name) {
		std::ifstream f(name.c_str());
		return f.good();
	}

	std::string convertWstringToString(const std::wstring & value);

	std::wstring convertStringtoWstring(const std::string & value);

	std::string findAndRepalce(const std::string &source,const std::string &a, const std::string & b);

	std::string convertVec2toString(const glm::vec2 & t_value);

	std::string convertVec3toString(const glm::vec3 & t_value);

	std::string convertiVec2toString(const glm::ivec2 & t_value);

	CEGUI::String WCharToUTF8(std::wstring const &s);

	CEGUI::String ws2s(const std::wstring& s);
	
	
	glm::vec2 convertStringToVec2(const std::string & x_string , const std::string & y_string);

	glm::vec3 convertStringToVec3(const std::string & x_string, const std::string & y_string , const std::string & z_string);
	
	std::string getPathName(const std::string & str);

	std::string getFileNameFromPath(const std::string & str);

	std::string getNonTypeFile(const std::string & str);

	std::string convertPreciousFloatToString(float value, int precious = 2);
	
	std::wstring convertPreciousFloatToWString(float value, int precious = 2);

	std::string convertVec2ToStringWithPrecious(const glm::vec2 & value, int precious);

	glm::vec2 convertProcVec2ToVec2(const Proc_Vec2 & v2);


	glm::vec3 convertProcVec3ToVec3(const Proc_Vec3 & v3);


	glm::vec4 convertProcVec4ToVec4(const Proc_Vec4 & v4);

	Proc_Vec2 convertVec2ToProcVec2(const glm::vec2 & v2);


	Proc_Vec3 convertVec3ToProcVec3(const glm::vec3 & v3);

	Proc_Vec4 convertVec4ToProcVec4(const glm::vec4 & v4);

	float randomFloat(float a, float b);

	int radndomInt(int a, int b);

	bool isNumber(const std::string& s);

	bool isFloat(const std::string & s);

	void setResolution(const glm::vec2 & resolution);

	glm::vec2 getResolution() const { return m_resolution; }
	

private:

	static feint_common *p_Instance;

	glm::vec2 m_resolution;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	
};
#endif 

