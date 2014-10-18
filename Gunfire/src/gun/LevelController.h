#ifndef GUN_LEVEL_CONTROLLER_H
#define GUN_LEVEL_CONTROLLER_H

#include <SFML\Graphics.hpp>

#include "Timer.h"
#include "EventBind.h"
#include "Level.h"

namespace gun
{
	class GameObject;
	class DiedEventArgs;

	class LevelController
	{
	public:
		LevelController() { }
		LevelController(const Level& level);

		void Initialize();
		void Cleanup();
		void Update(double dt);

	private:
		static const int TIME_BONUS_MULTIPLIER;
		static const int POINTS_PER_LIFE;
		static const int SPEED_POWERUP_RATE;
		static const int FIRE_RATE_POWERUP_RATE;
		static const int GHOSTING_POWERUP_RATE;
		
		double wave_age_;
		double wave_point_age_;
		Level level_;
		int wave_index_;
		int wave_point_index_;
		Timer wave_delay_timer_;
		EventBind died_bind_;

		void Handle_Died(DiedEventArgs& args);
		WavePoint GetCurrentWavePoint();
		bool HasWavePoints();
		void StepWavePoint();
		void SetupWavePoint();
		void AddToScore(int points);
		void CheckEndGame();
		int CalculateTimeBonus();
		sf::Vector2f GetBoundaryPoint(const sf::Vector2f object_size);
	};
}

#endif