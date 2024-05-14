#pragma once
#include "EnemyBulletBase.h"


#define BORDER_X_LINE 350

#define BORDER_Y_LINE 300


class EnemyBullet_KomachiCoin : public EnemyBulletBase 
{
    public : 
        EnemyBullet_KomachiCoin();
        ~EnemyBullet_KomachiCoin();

        void update(float deltaTime);

        void initTierSetting(const std::vector<std::string> & spriteDatas);

        void setTier(int val);

        int getTier() const {return m_tier;}

    private :

        int m_tier;
        std::vector<Feintgine::F_Sprite> m_tierSprites;
    


};