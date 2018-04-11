#include "imgui.h"
#include "imgui-SFML.h"
#include "FastNoise.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>


sf::Texture makeTexture(int w, int h)
{
	sf::Texture texture;
	texture.create(w, h);

	sf::Image img;
	img.create(w, h);

	FastNoise noise;
	noise.SetNoiseType(FastNoise::NoiseType::Cellular);

	for (int x = 0; x < w; ++x)
	{
		for (int y = 0; y < h; ++y)
		{
			auto sample = noise.GetNoise(x, y);
			auto value = (int)(sample * 255.f);
			img.setPixel(x, y, sf::Color(value, value, value, 255));
		}
	}

	texture.update(img);

	return texture;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Map Generator");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	auto myTexture = makeTexture(512, 512);
	sf::Sprite sprite;
	sprite.setTexture(myTexture);

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		if (ImGui::Begin("Map"))
		{
			auto size = ImGui::GetWindowSize();
			auto xScale = size.x / myTexture.getSize().x;
			auto yScale = size.y / myTexture.getSize().y;

			float factor = 0.90f;
			sprite.setScale(xScale * factor, yScale * factor);

			ImGui::Image(sprite);
			
			ImGui::End();
		}

		window.clear(sf::Color(255,255,255,255));
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}
