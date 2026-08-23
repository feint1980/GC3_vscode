
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
#include "InfoHolder.h"

#include <TextRenderer.h>
#include "Banner.h"

#include "CombatGUIDock.h"

#include <algorithm>
#include <nlohmann/json.hpp>

#include "FieldInfo.h"
using json = nlohmann::json;

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

// combine hash map, yeah bro, IDK it either.
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

    void updateEvents();

    void addSlot(int collumn, int row, int side);

    void drawText(TextRenderer * textRenderer);

    CSlot * getSlot(int collumn, int row, int side);

    CSlot * getSlot(SlotPos pos);

    CombatCharacter * addCharacter(int collumn, int row, int side, const std::string & characterID, const std::string & portraitPath, const glm::vec2 & scale = glm::vec2(1.0f, 1.0f));

    dCharacterStats * addCharacterStats(const std::string & characterID, int side, const std::string & statsStr);

    CombatCharacter * getCharacter(const std::string & characterID, int side);

    Banner  * getBanner() { return m_banner; }

    // FieldInfo * getFieldInfo() { return &m_fieldInfo; }

    void setFieldInfoCharacter(const std::string & characterID, int side, const dCharacterStats & charStat); //{ m_fieldInfo.addCharacter(characterID, side, charStat); }

    void listFieldInfoCharacters();

    void characterMoveToCell(const std::string & characterID, int side, int col, int row, float duration);

    void characterPlayAnimation(const std::string & characterID, int side, const std::string & animName, bool loop);

    CombatCharacter * getCharacterByMouse(glm::vec2 mousePos);

    void registerCamera(Feintgine::Camera2D * camera) { m_tCam = camera; }

private:

    lua_State * m_script = nullptr;

    std::vector<CSlot> m_slots;

    // std::unordered_map<glm::ivec3, int> m_slotIndexMap;

    std::unordered_map<std::tuple<int, int, int>, int, TupleHash> m_slotIndexMap;
    // std::unordered_map<glm::ivec3 , int> m_slotIndexMap;

    std::unordered_map<int, glm::ivec3> m_enumToIndecies; 

    std::vector<std::shared_ptr<CombatCharacter>> m_characters; // iterate 

    std::unordered_map<std::string, std::shared_ptr<CombatCharacter>> m_charactersMap; // lookup

    std::unordered_map<std::string, std::string> m_portraitMap;

    // std::unordered_map<std::string, std::shared_ptr<dCharacterStats>> m_characterStatsMap;

    EmptyObject m_bg;

    Banner * m_banner = nullptr;

    CombatGUIDock m_guidock; 

    Feintgine::Camera2D * m_tCam = nullptr; // cam needed for position conversion 

    //std::unordered_map<std::string, std::string> m_portraitMap;

   // FieldInfo m_fieldInfo; // may flag as unused 


};


#endif // COMBAT_FIELD_H