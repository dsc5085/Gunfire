#include "ScreenManager.h"
#include "ContainerUtility.h"
#include "Log.h"
#include "InputContext.h"
#include "Screen.h"

gun::ScreenManager::ScreenManager()
	: is_running_(true)
{
}

void gun::ScreenManager::Stop()
{
	is_running_ = false;
}

void gun::ScreenManager::AddScreen(Screen* screen)
{
	if(!ContainerUtility::Exists(screens_, screen)
		&& !ContainerUtility::Exists(screens_to_add_, screen))
	{
		screens_to_add_.push_back(screen);
	}
}

void gun::ScreenManager::RemoveScreen(Screen* screen)
{
	if(ContainerUtility::Exists(screens_, screen)
		&& !ContainerUtility::Exists(screens_to_remove_, screen))
	{
		screens_to_remove_.push_back(screen);
	}
}

void gun::ScreenManager::Update(double dt, const std::vector<sf::Event>& current_events)
{
	InputContext input_context(current_events);

	for(boost::ptr_vector<Screen>::iterator i = screens_.begin(); 
		i != screens_.end(); i++)
	{
		i->HandleInput(input_context);
	}

	for(boost::ptr_vector<Screen>::iterator i = screens_.begin(); 
		i != screens_.end(); i++)
	{
		if(i->is_active())
		{
			i->Update(dt);
		}
	}

	while(!screens_to_add_.empty())
	{
		Screen* added_screen = screens_to_add_.back();
		added_screen->set_screen_mgr(this);
		added_screen->Initialize();
		screens_.push_back(added_screen);
		screens_to_add_.pop_back();
	}

	while(!screens_to_remove_.empty())
	{
		Screen* removed_screen = screens_to_remove_.back();
		removed_screen->Cleanup();
		ContainerUtility::RemoveElement<Screen>(screens_, removed_screen);
		screens_to_remove_.pop_back();
	}
}

void gun::ScreenManager::Draw(sf::RenderWindow& window)
{
	screens_.sort(ScreenDrawOrderComparer());

	for(boost::ptr_vector<Screen>::iterator i = screens_.begin(); 
		i != screens_.end(); i++)
	{
		if(i->is_visible())
		{
			i->Draw(window);
		}
	}
}