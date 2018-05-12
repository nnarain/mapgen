#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "windows/map_display_window.h"
#include "windows/parameter_window.h"
#include "parameters/parameter_loader.h"
#include "generator/map_generator.h"
#include "generator/map_generator_manager.h"
#include "script/script_engine.h"

#include <iostream>

static const int BUFFER_SIZE = 512;

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cerr << "Invalid number of arguments" << std::endl;
		return 1;
	}

    try
    {
        // Load parameters
        const std::string param_file(argv[2]);
        ParameterLoader loader(param_file);
        auto& parameters = loader.getParams();

        std::string script = std::string(argv[1]);
        ScriptEngine engine(script);

        MapGeneratorManager generator_manager(engine, parameters, BUFFER_SIZE);

        // Create ui components
        ParameterWindow parameter_window(parameters);
        parameter_window.setSaveCallback([&] {
            loader.save();
        });

        MapDisplayWindow map_display_window(generator_manager, BUFFER_SIZE);

        // Init SFML
        sf::RenderWindow window(sf::VideoMode(1080, 720), "Map Generator");
        window.setFramerateLimit(60);
        ImGui::SFML::Init(window);

        sf::Clock deltaClock;
        bool first_pass = true;

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
            bool params_updated = parameter_window.update();

            if (params_updated || first_pass)
            {
                generator_manager.generate();
                first_pass = false;
            }

            map_display_window.update();

            if (generator_manager.isUpdateReady())
            {
                map_display_window.updateTexture(static_cast<sf::Uint8*>(generator_manager.getBufferData()));
            }

            // re-draw the screen
            window.clear(sf::Color(128, 128, 128, 255));
            ImGui::SFML::Render(window);
            window.display();
        }
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
    
	ImGui::SFML::Shutdown();

	return 0;
}
