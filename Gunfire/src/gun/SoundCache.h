#ifndef GUN_SOUND_CACHE_H
#define GUN_SOUND_CACHE_H

#include <deque>
#include <map>
#include <boost\ptr_container\ptr_deque.hpp>
#include <SFML\Audio.hpp>

#include "SoundKey.h"
#include "MusicKey.h"

namespace gun
{
	class SoundCache
	{
	public:
		SoundCache();

		void PlaySound(SoundKey::Enum sound_key);
		void PlayMusic(MusicKey::Enum music_key);
		void Update(double dt);

	private:
		std::map<SoundKey::Enum, sf::Sound> sound_cache_;
		std::map<SoundKey::Enum, sf::SoundBuffer> sound_buffer_cache_;
		std::map<MusicKey::Enum, std::string> music_map_;

		// Using deque because vector resizes, destroys, and recreates it's 
		// objects.  Thus, the sounds periodically stop playing because they
		// get destroyed.
		std::deque<sf::Sound> active_sounds_;
		boost::ptr_deque<sf::Music> active_musics_;

		void LoadSounds();
		void LoadSoundBuffers();
		void LoadSoundBuffer(SoundKey::Enum sound_key, const std::string& file);
		void LoadMusicMap();
	};
}

#endif