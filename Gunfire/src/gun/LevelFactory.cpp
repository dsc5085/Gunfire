#include "LevelFactory.h"
#include "Paths.h"
#include "Level.h"
#include "Wave.h"
#include "WaveLoader.h"

gun::Level gun::LevelFactory::CreateLevel()
{
	Level level = Level();
	level.area = sf::FloatRect(0, 0, 32, 24);
	level.waves = WaveLoader::LoadWaves(Paths::WAVES_FILE);
	return level;
}