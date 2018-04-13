#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "windows/map_display_window.h"
#include "windows/parameter_window.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Map Generator");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	ParameterWindow config_window;
	MapDisplayWindow map_display_window(512, 512);

	sf::Clock deltaClock;

	while (window.isOpen()) 
	{
		// poll events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// pass events to imgui
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// update imgui
		ImGui::SFML::Update(window, deltaClock.restart());
		
		// draw gui
		config_window.render(window);
		map_display_window.render(window);

		if (config_window.updated())
		{
			const auto& config = config_window.getConfiguration();
		}

		// re-draw the screen
		window.clear(sf::Color(255, 255, 255, 255));
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}
