#ifndef WINDOWS_CONFIG_WINDOW_H
#define WINDOWS_CONFIG_WINDOW_H

#include "windows/window.h"
#include "parameters/parameter_value.h"
#include "parameters/noise_parameters.h"

#include <imgui.h>

#include <string>
#include <map>

class ParameterWindow : Window
{
	using GeneratorParameters = std::map<std::string, ParameterValue>;

public:
	ParameterWindow() : updated_(false)
	{

	}

	void render(sf::Window& window, std::map<std::string, GeneratorParameters>& params)
	{
		if (ImGui::Begin("Parameters", &opened_))
		{
			for (auto& it : params)
			{
				auto& name = it.first;
				auto& params = it.second;

				ImGui::Text(name.c_str());

				for (auto& it : params)
				{
					auto& field_name = it.first;
					auto& param_value = it.second;

					if (param_value.type == ParameterValue::Type::Scalar)
					{
						ImGui::InputFloat(field_name.c_str(), &param_value.param.value);
					}
					else if (param_value.type == ParameterValue::Type::Noise)
					{
						if (ImGui::TreeNode(&field_name, field_name.c_str()))
						{
							renderNoiseParams(param_value.param.noise);
							ImGui::TreePop();
						}
					}
				}

				ImGui::Separator();
			}

			if (ImGui::Button("Save"))
			{
				// ...
			}

			ImGui::End();
		}
	}

	bool updated() const
	{
		return updated_;
	}

	const NoiseParameters& getConfiguration() const
	{
		return params_;
	}

private:
	void renderNoiseParams(NoiseParameters& params)
	{
		static const char* noise_types[] = {
			"Value", "Value Fractal", "Perlin", "Perlin Fractal", "Simplex", "Simplex Fractal",
			"Cellular", "WhiteNoise", "Cubic", "Cubic Fractal"
		};
		static const char* interp_types[] = {
			"Linear", "Hermite", "Quintic"
		};
		static const char* fractal_types[] = {
			"FBM", "Billow", "RigidMulti"
		};

		ImGui::Combo("Noise Type", &params.noise_type, noise_types, IM_ARRAYSIZE(noise_types));
		ImGui::Combo("Interp Type", &params.interp_type, interp_types, IM_ARRAYSIZE(interp_types));
		ImGui::Combo("Fractal Type", &params.fractal_type, fractal_types, IM_ARRAYSIZE(fractal_types));
		ImGui::SliderInt("seed", &params.seed, -10000, +10000);
		ImGui::SliderInt("octaves", &params.octaves, 0, 10);
		ImGui::InputFloat("frequency", &params.frequency);
		ImGui::SliderFloat("gain", &params.gain, 0, 1);
		ImGui::SliderFloat("lacunarity", &params.lacunarity, 1, 2);
	}

	bool opened_;
	bool updated_;

	NoiseParameters params_;
};

#endif  // WINDOWS_CONFIG_WINDOW_H
