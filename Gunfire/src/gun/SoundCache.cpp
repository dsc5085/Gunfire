#include "SoundCache.h"
#include "Paths.h"

gun::SoundCache::SoundCache()
{
	LoadSoundBuffers();
	LoadSounds();
	LoadMusicMap();
}

void gun::SoundCache::PlaySound(SoundKey::Enum sound_key)
{
	active_sounds_.push_back(sound_cache_[sound_key]);
	active_sounds_.back().play();
}

void gun::SoundCache::PlayMusic(MusicKey::Enum music_key)
{
	active_musics_.push_back(new sf::Music());
	std::string file_name = music_map_[music_key];
	if (!active_musics_.back().openFromFile(file_name))
	{
		std::string message = "Couldn't load music file " + file_name;
		throw std::invalid_argument(message);
	}
	active_musics_.back().play();
}

void gun::SoundCache::Update(double dt)
{
	for (unsigned int i = 0; i < active_sounds_.size(); i++)
	{
		if (active_sounds_[i].getStatus() == sf::Sound::Stopped)
        {
			active_sounds_.erase(active_sounds_.begin() + i);
			--i;
		}
	}

	for (unsigned int i = 0; i < active_musics_.size(); i++)
	{
		if (active_musics_[i].getStatus() == sf::Music::Stopped)
		{
			active_musics_[i].play();
		}
	}
}

void gun::SoundCache::LoadSounds()
{
	sound_cache_[SoundKey::MENU_SELECT] = sf::Sound(
		sound_buffer_cache_[SoundKey::MENU_SELECT]);
	sound_cache_[SoundKey::GUN_SHOT] = sf::Sound(
		sound_buffer_cache_[SoundKey::GUN_SHOT]);
	sound_cache_[SoundKey::LASER] = sf::Sound(
		sound_buffer_cache_[SoundKey::LASER]);
	sound_cache_[SoundKey::ARCADE_EXPLOSION] = sf::Sound(
		sound_buffer_cache_[SoundKey::ARCADE_EXPLOSION]);
	sound_cache_[SoundKey::PAIN] = sf::Sound(
		sound_buffer_cache_[SoundKey::PAIN]);
	sound_cache_[SoundKey::ZOMBIE_ATTACKED] = sf::Sound(
		sound_buffer_cache_[SoundKey::ZOMBIE_ATTACKED]);
	sound_cache_[SoundKey::MALE_YES] = sf::Sound(
		sound_buffer_cache_[SoundKey::MALE_YES]);
}

void gun::SoundCache::LoadSoundBuffers()
{
	LoadSoundBuffer(SoundKey::MENU_SELECT, Paths::SOUNDS_DIR + "menu_move.wav");
	LoadSoundBuffer(SoundKey::GUN_SHOT, Paths::SOUNDS_DIR + "silencer.wav");
	LoadSoundBuffer(SoundKey::LASER, Paths::SOUNDS_DIR + "laser.wav");
	LoadSoundBuffer(SoundKey::ARCADE_EXPLOSION, Paths::SOUNDS_DIR + "arcade_explosion.ogg");
	LoadSoundBuffer(SoundKey::PAIN, Paths::SOUNDS_DIR + "pain.ogg");
	LoadSoundBuffer(SoundKey::ZOMBIE_ATTACKED, Paths::SOUNDS_DIR + "zombie_attacked.ogg");
	LoadSoundBuffer(SoundKey::MALE_YES, Paths::SOUNDS_DIR + "male_yes.ogg");
}

void gun::SoundCache::LoadSoundBuffer(
	SoundKey::Enum sound_key, const std::string& file)
{
	sf::SoundBuffer sound_buffer = sf::SoundBuffer();
	sound_buffer.loadFromFile(file);
	sound_buffer_cache_[sound_key] = sound_buffer;
}

void gun::SoundCache::LoadMusicMap()
{
	music_map_[MusicKey::WILD_ONES] = Paths::SOUNDS_DIR + "wildones.ogg";
}