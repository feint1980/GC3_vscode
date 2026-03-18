
#ifndef COMBAT_FIELD_H
#define COMBAT_FIELD_H
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <vector>
#include <SpriteBatch.h>
#include <SDL2/SDL_keyboard.h>
#include <GLTexture.h>
#include <ResourceManager.h>

#include "LuaManager.h"

#include "CSlot.h"
#include "CombatCharacter.h"

enum SlotPos
{
    // Left
    LeftRearTop,
    LeftCenterTop,
    LeftFrontTop,
    LeftRearMid,
    LeftCenterMid,
    LeftFrontMid,
    LeftRearBot,
    LeftCenterBot,
    LeftFrontBot,
    // Right
    RightRearTop,
    RightCenterTop,
    RightFrontTop,
    RightRearMid,
    RightCenterMid,
    RightFrontMid,
    RightRearBot,
    RightCenterBot,
    RightFrontBot
};

#define FIELD_SIDE_LEFT 1
#define FIELD_SIDE_RIGHT 2

#include <unordered_map>
#include <tuple>

struct TupleHash {
    template <typename... T>
    size_t operator()(const std::tuple<T...>& t) const {
        size_t seed = 0;
        std::apply([&seed](const auto&... args) {
            ((seed ^= std::hash<std::decay_t<decltype(args)>>{}(args)
                      + 0x9e3779b9 + (seed << 6) + (seed >> 2)), ...);
        }, t);
        return seed;
    }
};




class CombatField
{
public:
    CombatField();
    ~CombatField();

    void init(const std::string & scriptPath, lua_State * script);

    void initSlots(int collumns, int rows);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

    void addSlot(int collumn, int row, int side);

    CSlot * getSlot(int collumn, int row, int side);

    CSlot * getSlot(SlotPos pos);

    void addCharacter(int collumn, int row, int side, const std::string & animationPath, const std::string & portraitPath, const glm::vec2 & scale = glm::vec2(1.0f, 1.0f));


private:

    lua_State * m_script = nullptr;

    std::vector<CSlot> m_slots;

    // std::unordered_map<glm::ivec3, int> m_slotIndexMap;


    std::unordered_map<std::tuple<int, int, int>, int, TupleHash> m_slotIndexMap;
    // std::unordered_map<glm::ivec3 , int> m_slotIndexMap;

    std::unordered_map<int, glm::ivec3> m_enumToIndecies; 


    std::vector<CombatCharacter> m_characters;

    EmptyObject m_bg;

};


#endif // COMBAT_FIELD_H