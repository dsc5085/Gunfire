#include "Screen.h"

gun::Screen::Screen()
	: draw_order_(0), is_active_(true), is_visible_(true)
{
}

gun::Screen::Screen(int draw_order)
	: draw_order_(draw_order), is_active_(true), is_visible_(true)
{
}