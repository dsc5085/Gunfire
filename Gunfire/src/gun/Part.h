#ifndef GUN_PART_H
#define GUN_PART_H

namespace gun
{
	class GameObject;

	class Part
	{
	public:
		bool is_active() const { return is_active_; }
		void set_is_active(bool is_active) { is_active_ = is_active; }
		void set_game_object(GameObject* game_object) { game_object_ = game_object; }

		Part();
		virtual ~Part() { }

		virtual void Initialize() { }
		virtual void Cleanup() { }
		virtual void Update(double dt) { }

	protected:
		bool is_active_;
		GameObject* game_object_;
	};
}

#endif