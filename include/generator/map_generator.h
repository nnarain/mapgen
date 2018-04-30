#ifndef GENERATOR_MAP_GENERATOR_H
#define GENERATOR_MAP_GENERATOR_H

#include <memory>
#include <string>
#include <vector>

#include "generator/generator_buffer.h"
#include "generator/generator_buffer_proxy.h"
#include "parameters/parameter_loader.h"

class MapGenerator
{
public:
	using Ptr = std::unique_ptr<MapGenerator>;
	using GeneratorBufferList = std::vector<GeneratorBufferProxy>;

	virtual void generate(GeneratorBufferList&) = 0;
	virtual void loadParams(ParameterLoader::GeneratorParameters&) = 0;

	virtual std::string getName() const = 0;
	virtual std::vector<std::string> getLayerNames() const = 0;

protected:
	ParameterValue & getParam(ParameterLoader::GeneratorParameters& params, const std::string& name)
	{
		for (auto& param : params)
		{
			if (param.first == name)
			{
				return param.second;
			}
		}

		throw std::runtime_error("Could not find parameter value");
	}

	NoiseParameters& getNoise(ParameterLoader::GeneratorParameters& params, const std::string& name)
	{
		return getParam(params, name).param.noise;
	}

	float* getColor(ParameterLoader::GeneratorParameters& params, const std::string& name)
	{
		return &getParam(params, name).param.color[0];
	}

	float getFloat(ParameterLoader::GeneratorParameters& params, const std::string& name)
	{
		return getParam(params, name).param.value;
	}
};

#endif  // GENERATOR_MAP_GENERATOR_H