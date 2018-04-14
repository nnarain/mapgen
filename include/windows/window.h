#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include <SFML/Window.hpp>

class Window
{
public:
	virtual bool update() { return false; }
};

#endif  // WINDOWS_WINDOW_H