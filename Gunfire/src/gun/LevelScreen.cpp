#include "LevelScreen.h"
#include "ScreenDrawOrder.h"
#include "CollidedEventArgs.h"
#include "GameOverEventArgs.h"
#include "GameObject.h"
#include "HighScoreEntryScreen.h"
#include "GameOverScreen.h"
#include "InputContext.h"
#include "Services.h"
#include "EventManager.h"
#include "ScreenManager.h"

gun::LevelScreen::LevelScreen(Level level)
	: Screen(ScreenDrawOrder::WORLD), level_(level), 
	event_manager_(Services::Instance().event_manager()), 
	object_manager_(Services::Instance().object_manager())
{
	Services::Instance().session().is_paused = false;
}

void gun::LevelScreen::Initialize()
{
	Services::Instance().session().lives = 5;
	Services::Instance().session().score = 0;
	level_controller_ = LevelController(level_);
	Services::Instance().set_level(level_);
	game_over_bind_ = Services::Instance().event_manager()->Subscribe<GameOverEventArgs>(
		boost::bind(&gun::LevelScreen::Handle_GameOver, this, _1));
	level_controller_.Initialize();
}

void gun::LevelScreen::Cleanup()
{
	level_controller_.Cleanup();
	object_manager_->Clear();
	game_over_bind_.Unsubscribe();
}

void gun::LevelScreen::HandleInput(const InputContext& input_context)
{
	if (input_context.IsKeyReleased(sf::Keyboard::Escape))
	{
		set_active(!is_active());
		Services::Instance().session().is_paused = !is_active();
	}
}

void gun::LevelScreen::Update(double dt)
{
	for(boost::ptr_vector<GameObject>::iterator i = object_manager_->begin(); 
		i != object_manager_->end(); i++)
	{
		if(i->is_active())
		{
			i->Update(dt);
			
			for(boost::ptr_vector<GameObject>::iterator j = i + 1; 
				j != object_manager_->end(); j++)
			{
				if(j->is_active())
				{
					if(i->coll_box().intersects(j->coll_box()))
					{
						event_manager_->Publish(CollidedEventArgs(&*i, &*j));
					}
				}
			}
		}
	}

	level_controller_.Update(dt);
	object_manager_->Update();
}

void gun::LevelScreen::Draw(sf::RenderWindow& window)
{
	for(boost::ptr_vector<GameObject>::iterator i = object_manager_->begin(); 
		i != object_manager_->end(); i++)
	{
		i->Draw(window);
	}
}

void gun::LevelScreen::Handle_GameOver(GameOverEventArgs& args)
{
	screen_mgr_->RemoveScreen(this);

	if ((int)Services::Instance().session().high_scores.size()
		< Services::Instance().session().MAX_HIGH_SCORES
		|| Services::Instance().session().score
		> Services::Instance().session().high_scores.back().score)
	{
		screen_mgr_->AddScreen(new HighScoreEntryScreen());
	}
	else
	{
		screen_mgr_->AddScreen(new GameOverScreen());
	}
}