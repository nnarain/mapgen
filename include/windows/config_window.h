#ifndef WINDOWS_CONFIG_WINDOW_H
#define WINDOWS_CONFIG_WINDOW_H

#include "windows/window.h"
#include "configuration.h"

#include <imgui.h>

class ConfigWindow : Window
{
public:
	ConfigWindow() : updated_(false)
	{

	}

	virtual void render(sf::Window& window) override
	{
		if (ImGui::Begin("Configuration", &opened_))
		{
			ImGui::SliderInt("seed", &config_.seed, -10000, +10000);
			ImGui::SliderInt("octaves", &config_.octaves, 0, 10);
			ImGui::InputFloat("frequency", &config_.frequency);
			ImGui::SliderFloat("gain", &config_.gain, 0, 1);
			ImGui::SliderFloat("lacunarity", &config_.lacunarity, 1, 2);
			ImGui::End();
		}
	}

	bool updated() const
	{
		return updated_;
	}

	const Configuration& getConfiguration() const
	{
		return config_;
	}

private:
	bool opened_;
	bool updated_;

	Configuration config_;
};

#endif  // WINDOWS_CONFIG_WINDOW_H
