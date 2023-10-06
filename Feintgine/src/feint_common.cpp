#include "feint_common.h"

feint_common *feint_common::p_Instance = 0;

feint_common::feint_common()
{
	srand(static_cast <unsigned> (time(0)));
}


feint_common::~feint_common()
{
	srand(static_cast <unsigned> (time(0)));

}

float feint_common::randomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}


int feint_common::radndomInt(int a, int b)
{
	return a + (rand() %b);
}

bool feint_common::isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
	
}

bool feint_common::isFloat(const std::string & s)
{
	std::istringstream iss(s);
	float f;
	iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
						  // Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

void feint_common::setResolution(const glm::vec2 & resolution)
{
	m_resolution = resolution;
}

float feint_common::getRandomNum(float low, float hight)
{
	return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hight - low)));
}

void feint_common::testPrintUtf8(const std::wstring & msg)
{
#ifdef _WIN32	
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
	std::wcout << msg << "\n";
#ifdef _WIN32
	_setmode(_fileno(stdout), _O_TEXT);
#endif
}

void feint_common::showMessageBox(const std::string & msgtitle, const std::string & msgcontent)
{
	const SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{ /* .colors (.r, .g, .b) */
		  /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{ 0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{ 0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		NULL, /* .window */
		msgtitle.c_str(), /* .title */
		msgcontent.c_str() , /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
	}
	if (buttonid == -1) {
		std::cout << "no selection\n";
		SDL_Log("no selection");
	}
	else {
		std::cout << "selection was "<< buttons[buttonid].text << "\n";
		SDL_Log("selection was %s", buttons[buttonid].text);
	}
}

bool feint_common::showConfirmationBox(const std::string & msgtitle, const std::string & msgcontent)
{
	const SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Cancel" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OK" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{ /* .colors (.r, .g, .b) */
		  /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{ 0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{ 0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		NULL, /* .window */
		msgtitle.c_str(), /* .title */
		msgcontent.c_str() , /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
	}
	if (buttonid == -1) {
		std::cout << "no selection\n";
		SDL_Log("no selection");
		return false;
	}
	else {
		
		std::cout << "selection was " << buttons[buttonid].text << "\n";
		SDL_Log("selection was %s", buttons[buttonid].text);
		if (buttonid == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

std::string feint_common::convertWstringToString(const std::wstring & value)
{
	return converter.to_bytes(value);
}

std::wstring feint_common::convertStringtoWstring(const std::string & value)
{
	return converter.from_bytes(value);
}

std::string feint_common::findAndRepalce(const std::string &source, const std::string &a, const std::string & b)
{
	std::string ft = source;
	std::cout << "replace" << a << " with " << b << "\n";
	while (ft.find(a[0]) < 0 || ft.find(a[0]) >= ft.size())
	{
		std::cout << "found a repalce" << ft.find(a[0]) <<"\n";
		ft[ft.find(a[0])] = b[0];
	}
	

	return ft;
}

std::string feint_common::convertVec2toString(const glm::vec2 & t_value)
{
	
	std::string result = "";
	result.append(std::to_string(t_value.x));
	result.append(",");
	result.append(std::to_string(t_value.y));
	return result;

}


std::string feint_common::convertVec3toString(const glm::vec3 & t_value)
{
	std::string result = "";
	result.append(std::to_string(t_value.x));
	result.append(",");
	result.append(std::to_string(t_value.y));
	result.append(",");
	result.append(std::to_string(t_value.z));
	return result;
}

std::string feint_common::convertiVec2toString(const glm::ivec2 & t_value)
{
	std::string result = "";
	result.append(std::to_string(t_value.x));
	result.append(",");
	result.append(std::to_string(t_value.y));
	return result;
}

CEGUI::String feint_common::WCharToUTF8(std::wstring const &s)
{
	size_t max_bytes = s.size() * 4 + 1;
	CHAR* buf = new CHAR[max_bytes];
	WideCharToMultiByte(CP_UTF8, 0, s.c_str(), -1, buf, max_bytes, 0, 0);
	CEGUI::String ret((CEGUI::utf8*)buf);
	delete buf;
	return ret;
}

CEGUI::String feint_common::ws2s(const std::wstring& s)
{
	size_t max_bytes = s.size() * 4 + 1;
	CHAR* buf = new CHAR[max_bytes];
	WideCharToMultiByte(CP_UTF8, 0, s.c_str(), -1, buf, max_bytes, 0, 0);
	CEGUI::String ret((CEGUI::utf8*)buf);
	delete buf;
	return ret;
}

glm::vec2 feint_common::convertStringToVec2(const std::string & x_string, const std::string & y_string)
{
	if (isFloat(x_string) && isFloat(y_string))
	{
		return glm::vec2(std::stof(x_string.c_str()), std::stof(y_string.c_str()));
	}	
	return glm::vec2(-1);
}

glm::vec3 feint_common::convertStringToVec3(const std::string & x_string, const std::string & y_string, const std::string & z_string)
{
	if (isFloat(x_string) && isFloat(y_string) && isFloat(z_string))
	{
		return glm::vec3(std::stof(x_string.c_str()), std::stof(y_string.c_str()), std::stof(z_string.c_str()));
	}
	return glm::vec3(-1);
}

std::string feint_common::getPathName(const std::string & str)
 {

	// std::cout << "scan on " << str << "\n";
		 char sep = '/';

// #ifdef _WIN32
// 		 sep = '\\';
// #endif

		 size_t i = str.rfind(sep, str.length());
		 if (i != std::string::npos) {
			// std::cout << "cliped " << str << "\n";
			 return(str.substr(0, i));
		 }
		 return("");	 
 }

 std::string feint_common::getFileNameFromPath(const std::string & str)
 {

	 // std::cout << "scan on " << str << "\n";
	 char sep = '/';


	 size_t i = str.rfind(sep, str.length());
	 if (i != std::string::npos) {
		
		 return(str.substr(i + 1, str.length() - i));
	 }
	 return("");
 }

 std::string feint_common::getNonTypeFile(const std::string & str)
 {
	 std::string mystr = str.substr(0, str.find("."));

	 return mystr;
 }

 std::string feint_common::convertPreciousFloatToString(float value, int precious )
 {
	 std::stringstream stream;
	 std::string str;
	 stream << std::fixed << std::setprecision(precious) << value;
	 str = stream.str();
	 return str;
 }



 std::wstring feint_common::convertPreciousFloatToWString(float value, int precious /*= 2*/)
 {
	 std::wstringstream stream;
	 std::wstring str;
	 stream << std::fixed << std::setprecision(precious) << value;
	 str = stream.str();
	 return str;
 }

 std::string feint_common::convertVec2ToStringWithPrecious(const glm::vec2 & value, int precious)
 {
	 std::string result = "";
	 std::stringstream stream;
	 stream << std::fixed << std::setprecision(precious) << value.x;
	 result.append(stream.str());
	 result.append(",");
	 stream.str("");
	 stream << std::fixed << std::setprecision(precious) << value.y;
	 result.append(stream.str());
	 return result;
 }

 glm::vec2 feint_common::convertProcVec2ToVec2(const Proc_Vec2 & v2)
 {
	 return glm::vec2(v2.valuex(), v2.valuey());

 }

 glm::vec3 feint_common::convertProcVec3ToVec3(const Proc_Vec3 & v3)
 {
	 return glm::vec3(v3.valuex(), v3.valuey(), v3.valuez());
 }

 glm::vec4 feint_common::convertProcVec4ToVec4(const Proc_Vec4 & v4)
 {
	 return glm::vec4(v4.valuex(), v4.valuey(), v4.valuez(), v4.valuew());
 }


 Proc_Vec2 feint_common::convertVec2ToProcVec2(const glm::vec2 & v2)
 {
	 Proc_Vec2 pv2;
	 pv2.set_valuex(v2.x);
	 pv2.set_valuey(v2.y);
	 return pv2;
 }

 Proc_Vec3 feint_common::convertVec3ToProcVec3(const glm::vec3 & v3)
 {
	 Proc_Vec3 pv3;
	 pv3.set_valuex(v3.x);
	 pv3.set_valuey(v3.y);
	 pv3.set_valuez(v3.z);
	 return pv3;
 }

 Proc_Vec4 feint_common::convertVec4ToProcVec4(const glm::vec4 & v4)
 {
	 Proc_Vec4 pv4;
	 pv4.set_valuex(v4.x);
	 pv4.set_valuey(v4.y);
	 pv4.set_valuez(v4.z);
	 pv4.set_valuew(v4.w);
	 return pv4;
 }



