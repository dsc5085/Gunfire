#include "LevelController.h"
#include "Math.h"
#include "PolygonMath.h"
#include "WavePoint.h"
#include "NewWaveEventArgs.h"
#include "WaveCompleteEventArgs.h"
#include "DiedEventArgs.h"
#include "GameOverEventArgs.h"
#include "GameObject.h"
#include "Services.h"
#include "EventManager.h"
#include "SoundCache.h"
#include "GameObjectQuery.h"
#include "GameObjectFactory.h"

const int gun::LevelController::TIME_BONUS_MULTIPLIER = 200;
const int gun::LevelController::POINTS_PER_LIFE = 10000;
const int gun::LevelController::SPEED_POWERUP_RATE = 20;
const int gun::LevelController::FIRE_RATE_POWERUP_RATE = 20;
const int gun::LevelController::GHOSTING_POWERUP_RATE = 50;

gun::LevelController::LevelController(const Level& level)
	: wave_age_(0), wave_point_age_(0), level_(level), wave_index_(0), wave_point_index_(0), 
	wave_delay_timer_(Timer(5, 0))
{
}

void gun::LevelController::Initialize()
{
	died_bind_ = Services::Instance().event_manager()->Subscribe<DiedEventArgs>(
		boost::bind(&gun::LevelController::Handle_Died, this, _1));
	sf::FloatRect level_area = Services::Instance().level().area;
	GameObjectFactory::Spawn(ObjectClass::PLAYER, PolygonMath::Center(level_area));
	SetupWavePoint();
}

void gun::LevelController::Cleanup()
{
	died_bind_.Unsubscribe();
}

void gun::LevelController::Update(double dt)
{
	WavePoint wave_point = GetCurrentWavePoint();
	int enemy_count = Services::Instance().object_query()
		->GetByCollisionType(CollisionType::ENEMY).size();

	if (!wave_delay_timer_.is_running())
	{
		// if wavepoint time limit reached and not last wave point OR
		// if all active enemies are dead and this is not the beginning of the wave.
		if ((wave_point_age_ >= wave_point.duration
			&& wave_point_index_ < (int)level_.waves[wave_index_].wave_points.size() - 1)
			|| (enemy_count <= 0 && wave_point_age_ > 0))
		{
			// if there are more wave points
			if (HasWavePoints())
			{
				// if this is the last wavepoint
				if (wave_point_index_ >= (int)level_.waves[wave_index_].wave_points.size() - 1)
				{
					// start the timer for the next wave to begin and start the
					// next wave timer.
					int time_bonus = CalculateTimeBonus();
					AddToScore(time_bonus);
					wave_delay_timer_.Start();
					Services::Instance().event_manager()->Publish(
						WaveCompleteEventArgs(wave_index_, time_bonus));
				}
				else
				{
					// immediately spawn the new enemies
					StepWavePoint();
					SetupWavePoint();
				}
			}
			else
			{
				// if there are no more enemies and no more wavepoints, the game is
				// over.
				if (enemy_count <= 0)
				{
					AddToScore(CalculateTimeBonus());
					Services::Instance().event_manager()->Publish(GameOverEventArgs());
				}
			}
		}
	}

	// if the wave time is reached, setup the new wave and stop the wave timer.
	if (wave_delay_timer_.Check())
	{
		StepWavePoint();
		SetupWavePoint();
	}

	wave_delay_timer_.Update(dt);
	wave_point_age_ += dt;
	wave_age_ += dt;
}

void gun::LevelController::Handle_Died(DiedEventArgs& args)
{
	AddToScore(args.game_object->points());

	if (args.game_object->coll_type() == CollisionType::ENEMY)
	{
		if (rand() % SPEED_POWERUP_RATE == 0)
		{
			GameObjectFactory::Spawn(
				ObjectClass::SPEED_POWER_UP, args.game_object->position());
		}
		if (rand() % FIRE_RATE_POWERUP_RATE == 0)
		{
			GameObjectFactory::Spawn(
				ObjectClass::FIRE_RATE_POWER_UP, args.game_object->position());
		}
		if (rand() % GHOSTING_POWERUP_RATE == 0)
		{
			GameObjectFactory::Spawn(
				ObjectClass::GHOSTING_POWER_UP, args.game_object->position());
		}
	}

	if (args.game_object->object_class() == ObjectClass::PLAYER)
	{
		Services::Instance().session().lives--;

		if (Services::Instance().session().lives > 0)
		{
			sf::FloatRect level_area = Services::Instance().level().area;
			GameObjectFactory::Spawn(ObjectClass::PLAYER, 
				PolygonMath::Center(level_area));
		}
		else
		{
			Services::Instance().event_manager()->Publish(GameOverEventArgs());
		}
	}
}

gun::WavePoint gun::LevelController::GetCurrentWavePoint()
{
	Wave wave = level_.waves[wave_index_];
	WavePoint wave_point = wave.wave_points[wave_point_index_];
	return wave_point;
}

bool gun::LevelController::HasWavePoints()
{
	Wave wave = level_.waves[wave_index_];
	return wave_index_ < (int)level_.waves.size() - 1
		|| wave_point_index_ < (int)wave.wave_points.size() - 1;
}

void gun::LevelController::StepWavePoint()
{
	Wave wave = level_.waves[wave_index_];
	wave_point_age_ = 0;
	wave_point_index_++;

	// If last wavepoint...
	if (wave_point_index_ >= (int)wave.wave_points.size())
	{
		// advance to next wave.
		wave_index_++;
		wave_age_ = 0;
		wave_point_index_ = 0;
		Services::Instance().event_manager()->Publish(NewWaveEventArgs(wave_index_));
	}
}

void gun::LevelController::SetupWavePoint()
{
	WavePoint wave_point = GetCurrentWavePoint();

	for (std::map<std::string, int>::iterator it = wave_point.objects.begin(); 
		it != wave_point.objects.end(); ++it)
	{
		for (int i = 0; i < it->second; i++)
		{
			GameObject* enemy = GameObjectFactory::CreateGameObject(
				it->first, sf::Vector2f(0, 0));
			sf::Vector2f position = GetBoundaryPoint(enemy->size());
			enemy->position() = position;
			Services::Instance().object_manager()->MarkAdded(enemy);
			enemy->Initialize();
		}
    }

	wave_delay_timer_.Stop();
}

void gun::LevelController::AddToScore(int points)
{
	int old_score = Services::Instance().session().score;
	Services::Instance().session().score += points;
	int lives_earned = Services::Instance().session().score / POINTS_PER_LIFE
		- old_score / POINTS_PER_LIFE;
	Services::Instance().session().lives += lives_earned;
}

int gun::LevelController::CalculateTimeBonus()
{
	Wave wave = level_.waves[wave_index_];
	int total_objects = 0;

	for (unsigned int i = 0; i < wave.wave_points.size(); i++)
	{
		std::map<std::string, int> objects = wave.wave_points[i].objects;

		for (std::map<std::string, int>::iterator it = objects.begin(); it != objects.end(); it++)
		{
			total_objects += it->second;
		}
	}

	// time bonus is calculated as the number of total objects in the completed wave
	// minus how many seconds it took to complete the wave, multiplied by a constant.
    int time_bonus = (total_objects - (int)wave_age_ / 2) * TIME_BONUS_MULTIPLIER;
	return std::max(0, time_bonus);
}

sf::Vector2f gun::LevelController::GetBoundaryPoint(const sf::Vector2f object_size)
{
	int random = rand() % 4;
	sf::FloatRect area = Services::Instance().level().area;
	sf::Vector2f position;

	if (random == 0)
	{
		// spawn on top edge
		float x = (float)Math::Random(0, area.left + area.width - object_size.x);
		position = sf::Vector2f(x, -object_size.y);
	}
	else if (random == 1)
	{
		// spawn on bottom edge
		float x = (float)Math::Random(0, area.left + area.width - object_size.x);
		position = sf::Vector2f(x, area.top + area.height);
	}
	else if (random == 2)
	{
		// spawn on left edge
		float y = (float)Math::Random(0, area.top + area.height - object_size.y);
		position = sf::Vector2f(-object_size.x, y);
	}
	else
	{
		// spawn on right edge
		float y = (float)Math::Random(0, area.top + area.height - object_size.y);
		position = sf::Vector2f(area.left + area.width, y);
	}

	return position;
}