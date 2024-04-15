#include "AudioEngine.h"
#include <SDL2/SDL_mixer.h>
#include "Error.h"
#include <iostream>

const int AUD_FREQ_LOW = 22050;
const int AUD_FREQ_HIGH = 44100;
const int AUD_VOLUME_MUSIC = 70;


namespace Feintgine
{
	AudioEngine::AudioEngine()
	{
	}


	AudioEngine::~AudioEngine()
	{
		destroy();
	}




	void AudioEngine::init()
	{
		if (Mix_Init(MIX_INIT_MP3) == -1)
		{
			fatalError(" audio ( MIX INIT FAILED ) due to " + std::string(Mix_GetError()));
		}
		if (Mix_OpenAudio(AUD_FREQ_LOW, MIX_DEFAULT_FORMAT, 1, 2048) == -1)
		{
			fatalError(" audio ( MIX Open Audio Failed ) due to " + std::string(Mix_GetError()));
		}
		Mix_VolumeMusic(AUD_VOLUME_MUSIC);
		
		

	}
	void AudioEngine::destroy()
	{
		if (m_isInitialized)
		{
			m_isInitialized = false;
			Mix_Quit();
		}
	}

	void AudioEngine::setVolume(int value)
	{
		Mix_Volume(-1,value);
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string  & filePath)
	{
		SoundEffect effect;
		auto it = m_soundEffectMap.find(filePath);
		if (it == m_soundEffectMap.end())
		{
			// not find , add to cache
			Mix_Chunk * chunk = Mix_LoadWAV(filePath.c_str());
			if (chunk == nullptr)
			{
				fatalError("error to load the File " +std::string(Mix_GetError()));
			}
			m_soundEffectMap[filePath] = chunk;
			effect.m_chunk = chunk;
		}
		else
		{
			// found it get from cache
			effect.m_chunk = it->second;
		}
		return effect;
	}
	Music AudioEngine::loadMusic(const std::string & filePath)
	{
		
		auto it = m_musicMap.find(filePath);
		Music music;
		if (it == m_musicMap.end())
		{
			// not find , add to cache
			Mix_Music * tempMusic = Mix_LoadMUS(filePath.c_str());
			if (tempMusic == nullptr)
			{
				fatalError("error to load the File " + std::string(Mix_GetError()));
			}
			else
			{
				std::cout << "loaded " + filePath;
			}
			m_musicMap[filePath] = tempMusic;
			music.m_music = tempMusic;
		}
		else
		{
			// found it get from cache
			music.m_music = it->second;
		}

		return music;
	}


	void SoundEffect::play(int loop)
	{
		Mix_VolumeChunk(m_chunk, AUD_VOLUME_SFX);
		if(Mix_PlayChannel(-1, m_chunk, loop) == -1)
		{
			if (Mix_PlayChannel(0, m_chunk, loop) == -1)
			{
				fatalError("error while playing Mix_PlayChannel " + std::string(Mix_GetError()));
			}
		}
	}

	void SoundEffect::playInChannel(int loop, int channel)
	{
		Mix_VolumeChunk(m_chunk, AUD_VOLUME_SFX);
		if (Mix_PlayChannel(channel, m_chunk, loop) == -1)
		{
			if (Mix_PlayChannel(0, m_chunk, loop) == -1)
			{
				fatalError("error while playing Mix_PlayChannel " + std::string(Mix_GetError()));
			}
		}
	}

	void SoundEffect::stahp()
	{
		//Mix_
		m_chunk->volume = 0;
	}

	void SoundEffect::setVolume(int val)
	{
		AUD_VOLUME_SFX = val;
		m_chunk->volume = val;
		//std::cout << "called " << val << "\n";
	}

	void Music::play(int loop)
	{
		if(Mix_PlayMusic(m_music, loop)== -1)
		{
			fatalError("error while playing Mix_PlayMusic " + std::string(Mix_GetError()));
		}
		std::cout << "played music \n";
	}
	void Music::pause()
	{
		Mix_PauseMusic(); 
	}
	void Music::resume()
	{
		Mix_ResumeMusic();
	}
	void Music::stahp()
	{
		Mix_HaltMusic();

	}
	AudioEngine *AudioEngine::p_Instance = 0;
}
