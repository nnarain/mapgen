#ifndef WINDOWS_CONFIG_WINDOW_H
#define WINDOWS_CONFIG_WINDOW_H

#include "windows/window.h"
#include "parameters/parameter_loader.h"
#include "parameters/parameter_value.h"
#include "parameters/noise_parameters.h"

#include <imgui.h>

#include <functional>
#include <string>
#include <map>


class ParameterWindow : Window
{
	using ParameterMap = std::map<std::string, ParameterLoader::GeneratorParameters>;
public:
	ParameterWindow(ParameterMap& param_map) :
		parameter_map_(param_map),
		opened_(false)
	{

	}

	virtual bool update(std::string& current_map)
	{
		bool param_updated = false;

		if (ImGui::Begin("Parameters", &opened_))
		{
			ImGui::Text(current_map.c_str());

			for (auto& it : parameter_map_[current_map])
			{
				auto& field_name = it.first;
				auto& param_value = it.second;

				if (param_value.type == ParameterValue::Type::Scalar)
				{
					param_updated = ImGui::InputFloat(field_name.c_str(), &param_value.param.value) || param_updated;
				}
				else if (param_value.type == ParameterValue::Type::Noise)
				{
					if (ImGui::TreeNode(&field_name, field_name.c_str()))
					{
						param_updated = renderNoiseParams(param_value.param.noise) || param_updated;
						ImGui::TreePop();
					}
				}
			}

			if (ImGui::Button("Save"))
			{
				if (save_callback_)
				{
					save_callback_();
				}
			}

			ImGui::End();
		}

		return param_updated;
	}

	void setSaveCallback(std::function<void()> fn)
	{
		save_callback_ = fn;
	}

private:
	bool renderNoiseParams(NoiseParameters& params)
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

		bool param_updated = false;
		param_updated = ImGui::Combo("Noise Type", &params.noise_type, noise_types, IM_ARRAYSIZE(noise_types)) || param_updated;
		param_updated = ImGui::Combo("Interp Type", &params.interp_type, interp_types, IM_ARRAYSIZE(interp_types)) || param_updated;
		param_updated = ImGui::Combo("Fractal Type", &params.fractal_type, fractal_types, IM_ARRAYSIZE(fractal_types)) || param_updated;
		param_updated = ImGui::SliderInt("seed", &params.seed, -10000, +10000) || param_updated;
		param_updated = ImGui::SliderInt("octaves", &params.octaves, 0, 10) || param_updated;
		param_updated = ImGui::InputFloat("frequency", &params.frequency) || param_updated;
		param_updated = ImGui::SliderFloat("gain", &params.gain, 0, 1) || param_updated;
		param_updated = ImGui::SliderFloat("lacunarity", &params.lacunarity, 1, 2) || param_updated;

		return param_updated;
	}

	ParameterMap& parameter_map_;
	bool opened_;
	std::function<void()> save_callback_;
};

#endif  // WINDOWS_CONFIG_WINDOW_H
