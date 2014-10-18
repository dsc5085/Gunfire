#include "Services.h"
#include "GameObject.h"
#include "EventManager.h"
#include "SpriteCache.h"
#include "SoundCache.h"
#include "ViewManager.h"
#include "GameObjectQuery.h"

gun::Services::Services()
	: event_manager_(new EventManager()), 
	object_manager_(new ObjectManager<GameObject>()), 
	object_query_(new GameObjectQuery()), 
	sprite_cache_(new SpriteCache()), 
	sound_cache_(new SoundCache()), 
	view_manager_(new ViewManager())
{
}