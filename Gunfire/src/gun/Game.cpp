#include "Game.h"
#include "FileIO.h"
#include "Paths.h"
#include "Log.h"
#include "ScoreEntry.h"
#include "MainMenuScreen.h"
#include "Services.h"
#include "SoundCache.h"
#include "ViewManager.h"

gun::Game::Game()
	: view_manager_(Services::Instance().view_manager())
{
}

void gun::Game::Run()
{
	try
	{
		Setup();

		// run the program as long as the window is open
		while (view_manager_->window().isOpen())
		{
			BOOST_LOG_TRIVIAL(trace) << "STEP";
			sf::Time time = clock_.getElapsedTime();
			clock_.restart();

			// check all the window's events that were triggered since the last iteration of the loop
			std::vector<sf::Event> events = std::vector<sf::Event>();
			sf::Event event;

			while (view_manager_->window().pollEvent(event))
			{
				events.push_back(event);
				// "close requested" event: we close the window
				if(event.type == sf::Event::Closed)
				{
					view_manager_->window().close();
				}
			}

			double dt = time.asSeconds();
			screen_manager_.Update(dt, events);
			Services::Instance().sound_cache()->Update(dt);

			if (!screen_manager_.is_running())
			{
				view_manager_->window().close();
			}

			view_manager_->window().clear();
			screen_manager_.Draw(view_manager_->window());
			view_manager_->window().display();
		}
	}
	catch (std::exception& ex)
	{
		BOOST_LOG_TRIVIAL(fatal) << "EXCEPTION: " << ex.what();
	}
}

void gun::Game::Setup()
{
	srand((unsigned int)time(0));
	Log::Initialize();
	LoadSettings();
	LoadHighScores();
	int screen_width = Services::Instance().session().screen_width;
	int screen_height = Services::Instance().session().screen_height;
	bool is_fullscreen = Services::Instance().session().is_fullscreen;
	view_manager_->SetWindowDisplay(is_fullscreen, screen_width, screen_height);
	view_manager_->world_view() = view_manager_->window().getDefaultView();
	view_manager_->window().setView(view_manager_->world_view());
	view_manager_->window().setFramerateLimit(60);
	screen_manager_.AddScreen(new MainMenuScreen());
}

void gun::Game::LoadSettings()
{
	std::vector<std::string> lines = FileIO::LoadLines(Paths::SETTINGS_FILE);

	if (lines.size() >= 11)
	{
		Services::Instance().session().is_fullscreen = lines[0] != "0";
		Services::Instance().session().screen_width = atoi(lines[1].c_str());
		Services::Instance().session().screen_height = atoi(lines[2].c_str());
		Services::Instance().session().input_map[InputAction::MOVE_UP]
			= (sf::Keyboard::Key)atoi(lines[3].c_str());
		Services::Instance().session().input_map[InputAction::MOVE_DOWN]
			= (sf::Keyboard::Key)atoi(lines[4].c_str());
		Services::Instance().session().input_map[InputAction::MOVE_LEFT]
			= (sf::Keyboard::Key)atoi(lines[5].c_str());
		Services::Instance().session().input_map[InputAction::MOVE_RIGHT]
			= (sf::Keyboard::Key)atoi(lines[6].c_str());
		Services::Instance().session().input_map[InputAction::FIRE_UP]
			= (sf::Keyboard::Key)atoi(lines[7].c_str());
		Services::Instance().session().input_map[InputAction::FIRE_DOWN]
			= (sf::Keyboard::Key)atoi(lines[8].c_str());
		Services::Instance().session().input_map[InputAction::FIRE_LEFT]
			= (sf::Keyboard::Key)atoi(lines[9].c_str());
		Services::Instance().session().input_map[InputAction::FIRE_RIGHT]
			= (sf::Keyboard::Key)atoi(lines[10].c_str());
	}
	else
	{
		throw std::runtime_error("Could not load settings.  Not enough parameters in "
			+ Paths::SETTINGS_FILE + ".");
	}
}

void gun::Game::LoadHighScores()
{
	std::vector<std::string> lines = FileIO::LoadLines(Paths::HIGH_SCORES_FILE);
	std::vector<ScoreEntry> high_scores = std::vector<ScoreEntry>();

	for (unsigned int i = 0; i < lines.size() / 2; i++)
	{
		ScoreEntry entry = ScoreEntry();
		entry.name = lines[i * 2];
		entry.score = atoi(lines[i * 2 + 1].c_str());
		high_scores.push_back(entry);
	}

	Services::Instance().session().high_scores = high_scores;
}