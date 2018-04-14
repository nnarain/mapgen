#ifndef FASTNOISE_GENERATOR_H
#define FASTNOISE_GENERATOR_H

#include "generator/map_generator.h"
#include "generator/pixel.h"
#include "parameters/parameter_loader.h"
#include "factory/fastnoise_factory.h"

#include <iostream>

class FastNoiseGenerator : public MapGenerator
{
public:
	FastNoiseGenerator(std::map<std::string, ParameterLoader::GeneratorParameters>& params):
		params_(params[getName()])
	{
		loadParams();
	}

	virtual void generate(GeneratorBufferList& buffers) override
	{
		const auto width = buffers[0].getWidth();
		const auto height = buffers[0].getHeight();

		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y)
			{
				auto sample = noise_.GetNoise(x, y);
			
				Pixel p;
				p.r = sample * 255.0f;
				p.g = sample * 255.0f;
				p.b = sample * 255.0f;

				buffers[0].write(x, y, p);
			}
		}
	}

	virtual void loadParams() override
	{
		noise_ = FastNoiseFactory::create(params_["noise"].param.noise);
	}

	virtual std::string getName() const override
	{
		return "FastNoise";
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