#pragma once

#include <vector>
#include <memory>
#include "f_anim.h"
namespace Feintgine {


	struct F_Animation
	{
	public:
		F_Animation();
		~F_Animation();
		void create(const std::string & animationName);


		void addAnim(const f_anim & tsprite, bool isLoop);

		void updateAnim(float deltaTime);

		void assignSpriteToCurrentAnim(const F_Sprite &sprite);

		void insertAnim();

		void removeAnimAt(int index);


		void playAnimation(int time, int index = 0);

		void setAnimation();

		void stop();

		bool isPlaying() const { return m_playing; }

		std::vector<f_anim> getAnims() { return m_anims; }
		std::string getAnimName() const { return m_animName; }

		f_anim * getCurrentAnim() const {
			return m_currentSprite;
		}

		void setCurrentAnimTime(float value);

		int getLoopAnim() const { return m_loop; }

		void setLoopAnim(int val);

		int getCurrentIndex() const { return m_curIndex; }

		size_t getSize() const { return m_anims.size(); }

		void setAnimIndex(int index);

		void resetAnim();

	private:

		std::vector<f_anim> m_anims;

		//std::weak_ptr <f_anim> m_currentSprite;
		std::shared_ptr<f_anim> m_currentSpriteGuard;
		f_anim * m_currentSprite;// = nullptr;
		std::string m_animName;
		int loopIndex = 0;

		bool m_loopSet = false;

		int m_curIndex = 0;
		float m_animTime = 0.0f;
		float m_animSpeed = 1.0f;

		int m_time = -1;

		int m_loop = 0;

		bool m_playing = false;
	};

}