
#ifndef _IOFILECACHE_H_
#define _IOFILECACHE_H_

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <rapidxml.hpp>
#include <vector>
#include <mutex>

using namespace rapidxml;
namespace Feintgine {
	class IOFileCache
	{
	public:
		IOFileCache();
		~IOFileCache();
	//	std::ifstream * getFilePreloaded(const std::string & filePath);

	//	xml_document<> getFullDoc(const std::string &filePath);
		std::vector<char> getBuffer(const std::string &filePath);
		std::vector<wchar_t> getBuffer(const std::string &filePath,bool isWchar);
	private:
		std::mutex m_mutex;
		std::map<std::string, std::vector<char> > m_xmlPreload;
		std::map<std::string, std::vector<wchar_t> > m_xmlwCharPreload;

	};
}

#endif