#ifndef WINDOWS_MAP_DISPLAY_WINDOW_H
#define WINDOWS_MAP_DISPLAY_WINDOW_H

#include "windows/window.h"

#include <imgui.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class MapDisplayWindow : Window
{
public:
	MapDisplayWindow(int w, int h)
	{
		texture_.create(w, h);
		sprite_.setTexture(texture_);
	}

	virtual bool update() override
	{
		if (ImGui::Begin("Map"))
		{
			ImGui::Image(sprite_);

			ImGui::End();
		}

		return false;
	}

private:
	sf::Texture texture_;
	sf::Sprite sprite_;
};

#endif  // WINDOWS_MAP_DISPLAY_WINDOW_H
