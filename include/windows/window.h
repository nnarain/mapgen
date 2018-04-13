#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include <SFML/Window.hpp>

class Window
{
public:
	virtual void render(sf::Window& window) {}
};

#endif  // WINDOWS_WINDOW_H