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
};

class W_Player : public W_BaseEntity
{
public:
    W_Player();
    ~W_Player() override;

    void initCharacter(const std::string & animationPath, int hpCap, int staminaCap);
    void update(float deltaTime) override;

    private:

    int m_hp = 100;
    int m_hpCap = 100;
    int m_stamina = 100;
    int m_staminaCap = 100;
};