#ifndef GUN_SERVICES_H
#define GUN_SERVICES_H

#include "Singleton.h"
#include "Session.h"
#include "Level.h"
#include "ObjectManager.h"

namespace gun
{
	class GameObject;
	class EventManager;
	class GameObjectQuery;
	class SpriteCache;
	class SoundCache;
	class ViewManager;

	class Services : public Singleton<Services>
	{
	public:
		EventManager* event_manager() { return event_manager_; }
		ObjectManager<GameObject>* object_manager() { return object_manager_; }
		GameObjectQuery* object_query() { return object_query_; }
		SpriteCache* sprite_cache() { return sprite_cache_; }
		SoundCache* sound_cache() { return sound_cache_; }
		ViewManager* view_manager() { return view_manager_; }
		Session& session() { return session_; }
		Level level() { return level_; }

		void set_level(Level level) { level_ = level; }

		Services();

	private:
		EventManager* event_manager_;
		ObjectManager<GameObject>* object_manager_;
		GameObjectQuery* object_query_;
		SpriteCache* sprite_cache_;
		SoundCache* sound_cache_;
		ViewManager* view_manager_;
		Session session_;
		Level level_;
	};
}

#endif