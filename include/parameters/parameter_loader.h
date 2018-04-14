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

	ParameterLoader(const std::string& file);

	std::map<std::string, GeneratorParameters>& getParams();

private:
	void load(YAML::Node& node);

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

	std::map<std::string, GeneratorParameters> generator_params;
};

#endif  // PARAMETERS_PARAMETER_LOADER_H
