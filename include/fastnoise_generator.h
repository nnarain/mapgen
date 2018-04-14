#ifndef FASTNOISE_GENERATOR_H
#define FASTNOISE_GENERATOR_H

#include "generator/map_generator.h"
#include "parameters/parameter_loader.h"
#include "factory/fastnoise_factory.h"

class FastNoiseGenerator : public MapGenerator
{
public:
	FastNoiseGenerator(ParameterLoader::GeneratorParameters& params):
		params_(params)
	{
		loadParams();
	}

	virtual void generate() override
	{

	}

	virtual void loadParams() override
	{
		noise_ = FastNoiseFactory::create(params_["noise"].param.noise);
	}

	virtual std::string getName() const override
	{
		return "FastNoise Generator";
	}

	virtual std::vector<std::string> getLayerNames() const override
	{
		return { "Default" };
	}

private:
	ParameterLoader::GeneratorParameters& params_;

	FastNoise noise_;
};

#endif // FASTNOISE_GENERATOR_H