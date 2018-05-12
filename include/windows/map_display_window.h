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
		current_generator_(0),
		current_layer_(0)
	{
		layer_names_ = manager.getCurrentLayerNames();

		texture_.create(texture_size, texture_size);
		sprite_.setTexture(texture_);
	}

	virtual bool update() override
	{
		if (ImGui::Begin("Map"))
		{
			drawMapSelection();

			if (ImGui::Button("Save"))
			{
				saveMap();
			}

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
		bool layer_changed = ImGui::Combo("Layers", &current_layer_, layer_names_, layer_names_.size());

		if (layer_changed)
		{
			manager_.setCurrentLayer(current_layer_);
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

	void saveMap()
	{
		const sf::Image image = texture_.copyToImage();
		image.saveToFile(getFileName());
	}

	std::string getFileName() const
	{
		return layer_names_[current_layer_] + ".png";
	}

	MapGeneratorManager& manager_;
	std::vector<std::string> layer_names_;

	int current_generator_ ;
	int current_layer_;

	sf::Texture texture_;
	sf::Sprite sprite_;
};

#endif  // WINDOWS_MAP_DISPLAY_WINDOW_H
