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

			auto& params = parameter_map_[current_map];

			// iterate and display parameters
			for (auto& it : params)
			{
				auto& field_name = it.first;
				auto& param_value = it.second;

				if (param_value.type == ParameterValue::Type::Scalar)
				{
					// display scalar values as floats
					param_updated = ImGui::DragFloat(field_name.c_str(), &param_value.param.value, 0.01f) || param_updated;
				}
				else if (param_value.type == ParameterValue::Type::Noise)
				{
					// nest noise params in a tree node
					if (ImGui::TreeNode(&field_name, field_name.c_str()))
					{
						param_updated = renderNoiseParams(param_value.param.noise) || param_updated;
						ImGui::TreePop();
					}
				}
				else if (param_value.type == ParameterValue::Type::Color)
				{
					param_updated = ImGui::ColorEdit4(
						field_name.c_str(),
						&param_value.param.color[0],
						ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoInputs) || param_updated;
				}
			}

			ImGui::Separator();
			renderAddParameters(params);
			ImGui::Separator();

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
	void renderAddParameters(ParameterLoader::GeneratorParameters& params)
	{
		ImGui::Text("New Parameter");
		static const char* new_parameter_options[] = { "Scalar", "Noise", "Color" };
		static int new_parameter_selection = 0;
		static char input_buffer[64];
		
		ImGui::InputText("name", input_buffer, 64);
		ImGui::Combo("type", &new_parameter_selection, new_parameter_options, IM_ARRAYSIZE(new_parameter_options));

		if (ImGui::Button("Add"))
		{
			std::string name(input_buffer);
			if (!name.empty())
			{
				ParameterValue value;
				value.name = name;
				value.type = static_cast<ParameterValue::Type>(new_parameter_selection);

				params.emplace_back(name, value);
			}
		}
	}

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
		static const char* cellular_distance_function[] = {
			"Euclidean", "Manhattan", "Natural"
		};
		static const char* cellular_return_type[] = {
			"CellValue", "NoiseLookup", "Distance", "Distance2",
			"Distance2Add", "Distance2Sub", "Distance2Mul", "Distance2Div" 
		};

		bool param_updated = false;
		param_updated = ImGui::Combo("Noise Type", &params.noise_type, noise_types, IM_ARRAYSIZE(noise_types)) || param_updated;
		param_updated = ImGui::DragInt("seed", &params.seed) || param_updated;
		param_updated = ImGui::DragFloat("frequency", &params.frequency, 0.01f) || param_updated;

		auto type = params.noise_type;

		// Interp type is only for value and perlin noise
		if (type <= 3)
		{
			param_updated = ImGui::Combo("Interp Type", &params.interp_type, interp_types, IM_ARRAYSIZE(interp_types)) || param_updated;
		}

		// fractal type is only for fractal noise
		if (type == 1 || type == 3 || type == 5 || type == 9)
		{
			param_updated = ImGui::Combo("Fractal Type", &params.fractal_type, fractal_types, IM_ARRAYSIZE(fractal_types)) || param_updated;
			param_updated = ImGui::SliderInt("octaves", &params.octaves, 0, 10) || param_updated;
			param_updated = ImGui::SliderFloat("gain", &params.gain, 0, 1) || param_updated;
			param_updated = ImGui::SliderFloat("lacunarity", &params.lacunarity, 1, 2) || param_updated;
		}

		if (type == 6)
		{
			param_updated = ImGui::Combo("Distance Func",
				&params.cellular_distance_function, cellular_distance_function, IM_ARRAYSIZE(cellular_distance_function)) || param_updated;
			param_updated = ImGui::Combo("Return Type",
				&params.cellular_return_type, cellular_return_type, IM_ARRAYSIZE(cellular_return_type)) || param_updated;
			param_updated = ImGui::InputFloat("jitter", &params.cellular_jitter) || param_updated;
		}

		return param_updated;
	}

	ParameterMap& parameter_map_;
	bool opened_;
	std::function<void()> save_callback_;
};

#endif  // WINDOWS_CONFIG_WINDOW_H
