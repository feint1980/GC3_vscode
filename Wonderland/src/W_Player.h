#include "W_BaseEntity.h"
#include <LuaManager.h>


class W_Player : public W_BaseEntity
{
public:
    W_Player();
    ~W_Player() override;

    void initCharacter(const std::string & luaFile, lua_State * script);
    void update(float deltaTime) override;

    private:
    lua_State * m_script;
};