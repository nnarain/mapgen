#ifndef PARAMETERS_PARAMETER_LOADER_H
#define PARAMETERS_PARAMETER_LOADER_H

#include "parameters/parameter_value.h"

#include <yaml-cpp/yaml.h>

#include <algorithm>
#include <array>
#include <map>
#include <string>
#include <iostream>

class ParameterLoader
{
public:
	using GeneratorParameters = std::map<std::string, ParameterValue>;

	ParameterLoader(const std::string& file)
	{
		auto root = YAML::LoadFile(file);
		load(root);
	}

	std::map<std::string, GeneratorParameters>& getParams()
	{
		return generator_params;
	}

private:
	void load(YAML::Node& node)
	{
		for (auto it = node.begin(); it != node.end(); ++it)
		{
			auto key = it->first.as<std::string>();
			auto params = loadGeneratorParams(it->second);

			generator_params[key] = params;
		}
	}

	GeneratorParameters loadGeneratorParams(YAML::Node& node)
	{
		GeneratorParameters params;
		
		for (auto it = node.begin(); it != node.end(); ++it)
		{
			auto key = it->first.as<std::string>();
			auto node = it->second;

			// check if the value is a float
			if (node.Type() == YAML::NodeType::Scalar)
			{
				ParameterValue value;
				value.name = key;
				value.type = ParameterValue::Type::Scalar;
				value.param.value = node.as<float>();

				params[key] = value;
			}
			else if (node.Type() == YAML::NodeType::Map)
			{
				if (node["noise_type"])
				{
					auto noise_params = loadNoiseParameter(node);

					ParameterValue value;
					value.name = key;
					value.type = ParameterValue::Type::Noise;
					value.param.noise = noise_params;

					params[key] = value;
				}
			}
		}

		return params;
	}

	NoiseParameters loadNoiseParameter(YAML::Node& node)
	{
		static std::array<std::string, 10> noise_types = {
			"value", "value_fractal", "perlin", "perlin_fractal", "simplex", "simplex_fractal",
			"cellular", "whitenoise", "cubic", "cubic_fractal" 
		};
		static std::array<std::string, 3> interp_types = {
			"Linear", "Hermite", "Quintic"
		};
		static std::array<std::string, 3> fractal_types = {
			"FBM", "Billow", "RigidMulti"
		};

		NoiseParameters params;

		// find the noise type
		auto noise_type = node["noise_type"].as<std::string>();
		params.noise_type = findIndex(noise_types, noise_type);

		// find interp type
		if (node["interp_type"])
		{
			auto interp_type = node["interp_type"].as<std::string>();
			params.interp_type = findIndex(interp_types, interp_type);
		}

		// find fractal type
		if (node["fractal_type"])
		{
			auto fractal_type = node["fractal_type"].as<std::string>();
			params.fractal_type = findIndex(fractal_types, fractal_type);
		}

		quickLoad(node, "seed", params.seed);
		quickLoad(node, "octaves", params.octaves);
		quickLoad(node, "frequency", params.frequency);
		quickLoad(node, "gain", params.gain);
		quickLoad(node, "lacunarity", params.lacunarity);

		return params;
	}

	template<class T, int N>
	int findIndex(const std::array<T, N>& a, const std::string& name)
	{
		auto found_iter = std::find(a.begin(), a.end(), name);
		int index = std::distance(a.begin(), found_iter);

		return index;
	}

	template<typename InputT>
	void quickLoad(YAML::Node& node, const std::string& name, InputT& i)
	{
		if (node[name])
		{
			i = node[name].as<InputT>();
		}
	}

	std::map<std::string, GeneratorParameters> generator_params;
};

#endif  // PARAMETERS_PARAMETER_LOADER_H
