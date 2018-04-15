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
	using ParameterMap = std::map<std::string, GeneratorParameters>;

	ParameterLoader(const std::string& file);

	void save();

	ParameterMap& getParams();

private:
	std::array<std::string, 10> noise_types_;
	std::array<std::string, 3> interp_types_;
	std::array<std::string, 3> fractal_types_;
	std::array<std::string, 3> cellular_distance_function_;
	std::array<std::string, 8> cellular_return_type_;

	void load(YAML::Node& node);

	void emitGeneratorParams(YAML::Emitter& out, GeneratorParameters& params);
	void emitNoiseParameters(YAML::Emitter& out, NoiseParameters& params);

	GeneratorParameters loadGeneratorParams(YAML::Node& node);
	NoiseParameters loadNoiseParameter(YAML::Node& node);

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

	ParameterMap generator_params_;
	std::string filename_;
};

#endif  // PARAMETERS_PARAMETER_LOADER_H
