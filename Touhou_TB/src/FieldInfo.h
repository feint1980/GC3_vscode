
#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <unordered_map>
#include <LuaManager.h>



class FieldInfo
{
public:
    FieldInfo();
    ~FieldInfo();

    void init(const std::string & scriptPath, lua_State * script);

    std::string getPortraitPath(const std::string & characterName);

    private:

    std::unordered_map<std::string, std::string> m_portraitMap;

    lua_State * m_script = nullptr;

};

#endif