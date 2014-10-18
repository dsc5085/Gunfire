#include <fstream>
#include <boost\algorithm\string.hpp>
#include <boost\lexical_cast.hpp>

#include "HighScoreEntryScreen.h"
#include "ScoreEntryComparer.h"
#include "PolygonMath.h"
#include "Paths.h"
#include "InputContext.h"
#include "TextFactory.h"
#include "HighScoresScreen.h"
#include "Services.h"
#include "Session.h"
#include "ScreenManager.h"
#include "ViewManager.h"

void gun::HighScoreEntryScreen::Initialize()
{
	text_factory_.Initialize();
	std::string score = boost::lexical_cast<std::string>(
		Services::Instance().session().score);
	sf::Vector2f screen_center = Services::Instance().view_manager()->world_view().getCenter();
	info_text_ = text_factory_.CreateText(24, 
		"NEW HIGH SCORE OF " + score +  "!  ENTER YOUR NAME:");
	info_text_.set_center(screen_center);
	name_text_ = text_factory_.CreateText(24, info_text_.position()
		+ sf::Vector2f(0, (float)info_text_.char_size()));
}

void gun::HighScoreEntryScreen::HandleInput(const InputContext& input_context)
{
	std::string string = name_text_.string();
	sf::Uint32 unicode = input_context.GetTextEnteredUnicode();

	if (unicode >= 0)
	{
		if(unicode == '\b' && string.length() > 0)
		{
			string.erase(string.length() - 1, 1);
		}
		else if(unicode < 128 && string.length() < 10)
		{
			sf::String ch(unicode);
			char ansi_ch = ch.toAnsiString()[0];

			if(ch.getSize() > 0 && isalnum(ansi_ch))
			{
				string += ch;
			}
		}
	}

	boost::to_upper(string);
	name_text_.set_string(string);
	
	if (input_context.IsKeyReleased(sf::Keyboard::Return))
	{
		EnterHighScores();
	}
}

void gun::HighScoreEntryScreen::Draw(sf::RenderWindow& window)
{
	info_text_.Draw(window);
	name_text_.Draw(window);
}

void gun::HighScoreEntryScreen::EnterHighScores()
{
	ScoreEntry high_score = ScoreEntry();
	high_score.name = name_text_.string();
	high_score.score = Services::Instance().session().score;
	Services::Instance().session().high_scores.push_back(high_score);
	std::sort(Services::Instance().session().high_scores.begin(), 
		Services::Instance().session().high_scores.end(), ScoreEntryComparer());

	while ((int)Services::Instance().session().high_scores.size()
		> Services::Instance().session().MAX_HIGH_SCORES)
	{
		Services::Instance().session().high_scores.pop_back();
	}

	SaveHighScores();
	screen_mgr_->RemoveScreen(this);
	screen_mgr_->AddScreen(new HighScoresScreen(high_score));
}

void gun::HighScoreEntryScreen::SaveHighScores()
{
	std::ofstream file = std::ofstream();
	file.open(Paths::HIGH_SCORES_FILE);
	std::vector<ScoreEntry> high_scores = Services::Instance().session().high_scores;

	for (unsigned int i = 0; i < high_scores.size(); i++)
	{
		file << high_scores[i].name << std::endl;
		file << high_scores[i].score << std::endl;
	}

	file.close();
}