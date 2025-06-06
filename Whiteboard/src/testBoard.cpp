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

    F_Lua_BaseEntity * f1 =  test(m_characters);
    std::cout << "end \n";
    std::cout << "Inserted successfully!" << std::endl;
    return 0;
}