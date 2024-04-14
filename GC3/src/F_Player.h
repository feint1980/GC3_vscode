
#pragma once
#include <AnimatedObject.h>
#include <InputManager.h>
#include <SDL2/SDL.h>
#include "F_PlayerAccessory.h"
#include "F_BulletStraight.h"
#include "F_EnemyBasic.h"
#include "ParticleBatch2D.h"
#include <IGameScreen.h>
#include "AudioEngine.h"
#include "EnemyBulletBase.h"
#include <TextRenderer.h>
#include "LabelItem.h"
#include "F_CollectableItem.h"
#include <math.h>
#include <LightBatch.h>
#include <F_AnimatedObject.h>
#include "GLTexture.h"
#include <F_SpellcardBase.h>
#include "F_Reimu_Fantasy_Seal_Obj.h"
#include "SpellcardSelector.h"
#include "F_Reimu_Demon_Binding.h"
#include <AfterImageParticle.h>

#include "Gohei_Rod.h"
#include "Yin_Yang_Orb.h"
#include "Yin_Yang_Orb_Ex.h"

#include "SealingAmulet.h"

#include "KanjiEffectManager.h"

#include <Box2D/Box2D.h>

#include "EnemyAmplifier.h"

#include "F_MarisaStarSpawner.h"

#include "F_Marisa_Luminous_Strike_Launcher.h"

#include "F_Player_Sun_Manager.h"

#include "F_Marisa_Star_Trail_Manager.h"
#include <chrono>


#include <EffectBatch.h>
//#include "F_RecordPlayer.h"

//#include "F_Marisa_MasterSpark.h"
class F_Marisa_MasterSpark;


class EnemyGuardian;

struct recordedState
{

	//std::chrono::system_clock::now()
	//event::time_type startTime;
	//SDL_GetTicks();
	//uint32 startTime;
	double startTime;
	//uint32 endTime;
	//double  endTime;
	unsigned long state;

	float x_pos;
	float y_pos;
};


struct recordedAction
{
	unsigned long tAction;
	//uint32 time;
	double time;

};


const int BORDER = 350;
 
const float LIMITED_ANGLE_MASTERSPARK = 15;

const int THE_POWER_OF = 2;

const float ENERGY_RATE = 0.025f;
const float MAX_ENERGY = 20.0f;
const float LOW_ENERGY_RATE = 10.0f;

// bitwise state
const unsigned long PLAYER_STATE_MOVE_LEFT = 1;
const unsigned long PLAYER_STATE_MOVE_RIGHT = 2;
const unsigned long PLAYER_STATE_MOVE_UP = 4;
const unsigned long PLAYER_STATE_MOVE_DOWN = 8;
const unsigned long PLAYER_STATE_IS_FOCUS = 16;
const unsigned long PLAYER_STATE_IS_FIRE = 32;
const unsigned long PLAYER_STATE_IS_ESCAPE_VEL = 64;


// non bitwise flag
const unsigned int PLAYER_ACTION_SWITCH_SPELL_FORWARD = 1;
const unsigned int PLAYER_ACTION_SWITCH_SPELL_PREVIOUS = 2;
const unsigned int PLAYER_ACTION_USE_SPELL = 3;


const unsigned int PLAYER_CHARACTER_REIMU = 1;
const unsigned int PLAYER_CHARACTER_MARISA = 2;
const unsigned int PLAYER_CHARACTER_PATCHOULI = 3;


struct F_PrimaryBullet
{
	bool isAnimated;
	std::string filePath;
	float dmg;
	float angle;

};

class F_Player
{
public:
	F_Player();
	~F_Player();

	void init(const std::string & animationPath, const std::string & accessorySprite, bool isShink = true);

	void registerEffectBatch(Feintgine::EffectBatch * effectBatch);

	void setPrimaryShot(bool t_isAnimated, const std::string & t_filePath, float t_dmg, float t_angle);

	void setPos(const glm::vec2 & pos);
	void setDim(const glm::vec2 & dim);

	void setVel(const glm::vec2 & vel);

	void setAccessoryShot(int val);
	glm::vec2 getPos() const { return m_pos; }
	glm::vec2 getDim() const { return m_dim; }

	glm::vec2 getVel() const { return m_vel; }
	void handleInput(Feintgine::InputManager & inputmanager);

	void setDeathCallback(const std::function <void(void)>& f);

	bool checkColliderWithEnemy(const F_BaseEnemy & enemy);
	bool checkColliderWithEnemyBullet(const EnemyBulletBase & bullet);

	void die();

	bool checkColliderWithGuardian(const EnemyGuardian & enemy);

	bool checkColliderWithCollectable( F_CollectableItem * item);

	bool checkGrazedEnemyBullet( EnemyBulletBase & bullet);

	void setOffsetNoLight(const glm::vec2 & offset);

	//void registerBox2DWorld(b2World * world);

	void fire();

	void setSpellPos(const glm::vec2 & pos);

	void update(float deltaTime , std::vector<F_BaseEnemy *>  m_enemies, 
		std::vector<EnemyBulletBase * > bullets, std::vector<EnemyGuardian *> guardians, std::vector<EnemyAmplifier *> amplifiers);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawLight(Feintgine::LightBatch &lightBatch);

	void drawHitbox(Feintgine::DebugRender & debugRenderer);

	void drawScore(TextRenderer & textRenderer, const Feintgine::Camera2D & cam);

	void drawText(TextRenderer & textRenderer, const Feintgine::Camera2D & cam);

	void registerLogicCamera(Feintgine::Camera2D * camera);

	Feintgine::ParticleBatch2D * getHitParticle() const { return m_hitParticleBatch; }

	//void updateParticle(Feintgine::Particle2D& particles, float deltatime);
	F_PlayerAccessory getLeftAccessosry(); 

	F_PlayerAccessory getRightAccesory(); 

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);

	void initSound();

	bool isDeath() const { return m_isDeath; }

	void clearBullet();

	Feintgine::AudioEngine * getAudioEngine() const { return m_audioEngine; }

	void setDepth(float depth);

	void onFocus();
	void offFocus();

	void setAccessoryLaser(const Feintgine::GLTexture & texture, const glm::vec2 & pos, const glm::vec2 & dim,
		const Feintgine::Color & color, float depth, float angle, float dps);

	void addScore(int score);
	void addScoreSilence(int score);

	int getScore() const { return m_score; }

	void setSpellSelectorPos(const glm::vec2 & pos);

	SpellcardSelector getSpellSelector() const { return m_spellSelector; }

	void reset();

	void addPower(unsigned int val);

	void drawNoLight(Feintgine::SpriteBatch & spriteBatch);

	void drawSpellSelector(Feintgine::SpriteBatch & spriteBatch);

	//void initCEGUIText();

	void addDropItem(F_CollectableItem * item);

	void popupLabel(const std::string & msg, const Feintgine::Color & color);

	unsigned int getGrazedPoint() const { return m_grazeCount; }

	void setInvinsible(bool val);

	void toggleInvinsible();

	Feintgine::F_AnimatedObject getAnimation() const { return m_animation; }

	void resetStack();

	void setFire(bool value);

	void setVolume(float value);

	bool changeColor(int channel, float rate, float maxVal);

	void unlockState(bool val);

	void setParentColor(bool val);

	void registerKanjiEffect(KanjiEffectManager * effectManager);

	std::wstring getSignFromTextureList(int val, int characterIndex);

	std::wstring getNameFromTextureList(int val, int characterIndex);

	int getGrazeFromTextureList(int val, int characterIndex);

	float getCDFromTextureList(int val, int characterIndex);

	void registerTextCEGUI(Feintgine::GUI & gui);

	void setFocus(bool val);

	void t_fantasySealOrbEndCallback();

	void updateMasterSparkMode(float deltaTime);

	void registerExplosionRing(std::vector<ExplosionRing> * rings);

	void updateEnergyLocked(float deltaTime);

	std::vector<F_BulletStraight *> getBullets() 
	{
		return m_bullets;
	}

	void escapeVelocity(int segment, float trailThreshold);

	void updateEscapeVelocity(float deltaTime);

	void spawnTrail(float deltaTime);

	void activeSpell();

	float decideDestination(float Xpos);

	void loadRecord(const std::string & filePath);

	void writeRecord(const std::string & filePath);

	glm::vec2 calculateNextLocation(const glm::vec2 & currentLoction, int & segmenntIndex);

	unsigned long  getPlayerState() const { return m_playerState; };
	unsigned int getPlayerAction() const { return m_PlayerAction; };

	void updateState(float deltaTime);

	void recordUpdate(float deltaTime);

	void addDistorionEffect(const glm::vec2 & pos,float size, float freq, float lifeTime ,float sizeRate, float freqRate);


	void addDistorionFollowEffect(glm::vec2 * pos, float size, float freq, float lifeTime, float sizeRate, float freqRate);

	void setCharacterSpell(unsigned int value);

	void clearData();

	//Feintgine::Color getColor() const { return m_colo}
protected:

	Feintgine::EffectBatch * m_effectBatch = nullptr;

	bool moveHor = true;
	bool moveVer = false;
	bool isMove = false;
	bool alreadySetLeft = false; 
	bool alreadySetRight = false;

	bool m_isControlable = true;
	glm::vec2 t_direction;
	bool m_firstVelocity = false;
	bool m_isPathDeciced = false;


	float m_velocityDesRate = 1.0f;
	float m_velocityDelayTimer = 3.5f;
	float m_velocityTimer = 0.0f;
	float m_velocityEscapeSpeed = 0.1f;
	bool m_velocotyEscapeLaserTrailSet = false;


	// escape velocity 
	int m_velocitySegment = 0;
	glm::vec2 mt_pos;
	glm::vec2 tg_pos;
	glm::vec2 m_trailPos;
	int m_velocityState = 0;
	glm::vec2 t_vel;

	float m_energy;


	float m_pernaltyRate = 1.2f;

	float m_energyCounter = 0.0f;
	//bool m_energySwitching = false;

	bool m_energyLocked = false;

	bool isIdled = false;
	glm::vec2 m_pos;
	glm::vec2 * p_pos;
	glm::vec2 m_dim; 
	glm::vec2 m_vel = glm::vec2(0);
	Feintgine::F_AnimatedObject m_animation;
	F_PlayerAccessory m_leftAccessory;
	F_PlayerAccessory m_rightAccessory; 

	glm::vec2 m_scale;

	bool m_isInvinsible = false;

	float delayBullet = 0.45f; //
	float fireRate = 0.0f;
	bool m_isAttack = false;

	std::vector<F_BulletStraight *> m_bullets;

	F_BulletStraight bullet;

	Feintgine::SoundEffect m_fireSoundEffect;

	Feintgine::SoundEffect m_deadSoundEffect;

	Feintgine::SoundEffect m_spellcardCastSoundEffect;

	Feintgine::SoundEffect m_dashSoundEffect;

	Feintgine::AudioEngine * m_audioEngine = nullptr;
	
	Feintgine::ParticleBatch2D * m_hitParticleBatch = nullptr;

	Feintgine::ParticleBatch2D * m_starParticleBatch1 = nullptr; 

	Feintgine::ParticleBatch2D * m_starParticleBatch2 = nullptr;// Luminous strike

	std::function <void(void)> m_deathCallback;

	std::vector<LabelItem> m_labelItems;

	std::vector<F_CollectableItem *> m_collectableItem;

	Feintgine::F_AnimatedObject m_testBulletAnimation;

	std::vector<F_SpellcardBase> m_spells;

	F_SpellcardBase m_fantasy_seal;

	unsigned int m_grazeCount = 300;

	int m_score = 0;

	unsigned int m_power;
	unsigned int m_powerLevel = 1; // min 1, max 6

	unsigned int m_startPower = 3;

	bool m_isFocus = false;
	bool m_isDeath = false;
	F_PrimaryBullet m_primary;

	bool isLocked = true;

	float m_speedPelnaty = 0.5f;

	bool isParentColor = false;

	SpellcardSelector m_spellSelector; 

	AfterImageObject m_afterImageParticle;

	std::vector<F_Reimu_Fantasy_Seal_Obj> m_flyOrb;

	F_Reimu_Demon_Binding * m_binding_circle = nullptr;

	Feintgine::Camera2D * m_logicCamera = nullptr;

	std::vector<ExplosionRing> * m_exlosions ;

	float m_afterImageTime = 0.0f;

	Gohei_Rod m_rod;

	Yin_Yang_Orb * m_yin_yang_orb = nullptr;
	Yin_Yang_Orb_Ex * m_yin_yang_orb_ex = nullptr;

	SealingAmulet m_sealingAmulet;

	F_Marisa_MasterSpark * m_masterSpark = nullptr;

	KanjiEffectManager * m_kanjiEffectManager_p = nullptr;

	F_MarisaStarSpawner m_starSpawner;

	Feintgine::F_AnimatedObject m_starAnim;

	F_Player_Sun_Manager m_suns;

	F_Marisa_Star_Trail_Manager m_starTrails;
	float m_trailThreshold;


	F_Marisa_Luminous_Strike_Launcher m_luminousLauncher;
	//float m_mas
	float m_masterSparkTime = 0.0f;
	float t_moveSpeed = 5.0f;
	float moveSpeed = 5.0f;

	bool m_masterSparkEnd = true;

	float m_angle = 0.0f;
	int m_angleFlag = 0;


	float m_unlimitedEnergyTimer = 1.0f;

	// for record 
	unsigned long m_playerState = 0;
	unsigned int m_PlayerAction = 0;

	//double current

	bool m_isReplay = false;
	int m_playerPrevState = 0;
	std::vector<recordedState> m_recordedStates;
	std::vector<recordedAction> m_recordedActions;

	std::vector<recordedState> m_loadedRecordedStates;
	std::vector<recordedAction> m_loadedRecordedActions;

	double m_currentTick;

	int m_currentRecordState;
	int m_currentRecordAction;

	Uint32 t_start;
	double t_duration;


	unsigned int m_characterType = PLAYER_CHARACTER_REIMU;
};

