#include "W_BaseEntity.h"
#include <LuaManager.h>
#include <InputManager.h>


enum W_PlayerAtt
{
    hp,
    hpCap,
    stamina,
    staminaCap,
    animationPath,
    walkSpeed,
    runSpeedScale,
    unknown
};

class W_Player : public W_BaseEntity
{
public:
    W_Player();
    ~W_Player() override;

    void initCharacter(const std::string & animationPath, int hpCap, int staminaCap);
    void update(float deltaTime);
    void setAttribute(const std::string & att, float value);
    void setAttribute(W_PlayerAtt att, float value);

    void setMovement(int flag) { m_movementFlag = flag; }
    W_PlayerAtt getAttribute(const std::string & att);

    private:

    int m_hp = 100;
    int m_hpCap = 100;
    int m_stamina = 100;
    int m_staminaCap = 100;
    float m_walkSpeed = 2.5f; 
    float m_runSpeedScale = 0;
    int m_movementFlag = 0; // 1 = left, 2 = right, 4 = up, 8 = down
    float m_crossScale = 0.5f;
    int m_movement = 0;

};