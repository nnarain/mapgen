#ifndef WINDOWS_MAP_DISPLAY_WINDOW_H
#define WINDOWS_MAP_DISPLAY_WINDOW_H

#include "windows/window.h"
#include "generator/map_generator_manager.h"

#include <imgui.h>
#include "imgui_extension/imgui_extension.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>

class MapDisplayWindow : Window
{
public:
	MapDisplayWindow(MapGeneratorManager& manager, int texture_size) :
		manager_(manager),
		selected_generator_(0)
	{
		generator_names_ = manager.getGeneratorNames();
		layer_names_ = manager.getCurrentLayerNames();

		texture_.create(texture_size, texture_size);
		sprite_.setTexture(texture_);
	}

	virtual bool update() override
	{
		if (ImGui::Begin("Map"))
		{
			drawMapSelection();
			drawMap();

			ImGui::End();
		}

		return false;
	}

	void updateTexture(sf::Uint8* buffer)
	{
		texture_.update(buffer);
	}

private:
	void drawMapSelection()
	{
		static int current_generator = 0;
		static int current_layer = 0;

		bool generator_changed = ImGui::Combo("Generators", &current_generator, generator_names_, generator_names_.size());

		if (generator_changed)
		{
			// if the generator has been updated, select the generator in the manager
			manager_.setCurrentGenerator(current_generator);
			layer_names_ = manager_.getCurrentLayerNames();

			current_layer = 0;

			// generate the new map
			manager_.generate();
		}

		bool layer_changed = ImGui::Combo("Layers", &current_layer, layer_names_, layer_names_.size());

		if (layer_changed)
		{
			manager_.setCurrentLayer(current_layer);
			manager_.setUpdateReady(true);
		}
	}

	void drawMap()
	{
		auto window_size = ImGui::GetContentRegionAvail();
		auto texture_size = texture_.getSize();
		auto x_scale = window_size.x / texture_size.x;
		auto y_scale = window_size.y / texture_size.y;
		sprite_.setScale(x_scale, y_scale);

		ImGui::Image(sprite_);
	}

	MapGeneratorManager& manager_;
	std::vector<std::string> generator_names_;
	std::vector<std::string> layer_names_;
	int selected_generator_;

	sf::Texture texture_;
	sf::Sprite sprite_;
};

#endif  // WINDOWS_MAP_DISPLAY_WINDOW_H
