#ifndef GUN_SCREEN_H
#define GUN_SCREEN_H

#include <SFML\Graphics.hpp>

namespace gun
{
	class ScreenManager;
	class InputContext;

	class Screen
	{
	public:
		bool is_active() const { return is_active_; }
		bool is_visible() const { return is_visible_; }
		int draw_order() const { return draw_order_; }

		void set_screen_mgr(ScreenManager* screen_mgr) { screen_mgr_ = screen_mgr; }
		void set_active(bool is_active) { is_active_ = is_active; }
		void set_visible(bool is_visible) { is_visible_ = is_visible; }
		
		Screen();
		Screen(int draw_order);

		virtual void Initialize() { }
		virtual void Cleanup() { }
		virtual void HandleInput(const InputContext& input_context) { }
		virtual void Update(double dt) { }
		virtual void Draw(sf::RenderWindow& window) { }

	protected:
		ScreenManager* screen_mgr_;

	private:
		bool is_active_;
		bool is_visible_;
		int draw_order_;
	};
}

#endif