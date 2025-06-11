#include <iostream>
#include <unordered_map>
#include <string>

class F_Lua_BaseEntity {
public:
    int x = 0;
};

std::unordered_map<std::string, F_Lua_BaseEntity*> m_characters;

F_Lua_BaseEntity * test(std::unordered_map<std::string, F_Lua_BaseEntity*> &characters) {
    F_Lua_BaseEntity * entity = new F_Lua_BaseEntity();
    std::string name = "test";
    characters[name] = entity;
    return entity;
}

int wmain() {

    std::string data = "this is the way";
    std::string tData = std::string(data.begin() + 3, data.end());

    std::cout << tData << "\n";

    return 0;
}