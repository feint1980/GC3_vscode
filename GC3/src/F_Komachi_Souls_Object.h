#ifndef _F_KOMACHI_SOULS_OBJECT_H_
#define _F_KOMACHI_SOULS_OBJECT_H_

#include <F_BaseObject.h>
#include <feint_common.h>

class F_Komachi_Souls_Object : public Feintgine::F_BaseObject
{
public:
    F_Komachi_Souls_Object();
    ~F_Komachi_Souls_Object();

    void update(float deltaTime) override;

    void randomlyDecide();
private :

    float m_decideTimer = 100.0f;
    glm::vec2 m_destination = glm::vec2(0.0f);

};



#endif // !_F_KOMACHI_SOULS_OBJECT_H_
