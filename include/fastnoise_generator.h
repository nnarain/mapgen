#ifndef FASTNOISE_GENERATOR_H
#define FASTNOISE_GENERATOR_H

#include "generator/map_generator.h"
#include "generator/color.h"
#include "parameters/parameter_loader.h"
#include "factory/fastnoise_factory.h"

#include <iostream>

class FastNoiseGenerator : public MapGenerator
{
public:
	FastNoiseGenerator()
	{
	}

	virtual void generate(GeneratorBufferList& buffers) override
	{
		const auto startX = buffers[0].startX();
		const auto startY = buffers[0].startY();
		const auto endX = buffers[0].endX();
		const auto endY = buffers[0].endY();

		for (int x = startX; x < endX; ++x)
		{
			for (int y = startY; y < endY; ++y)
			{
				auto sample = noise_.GetNoise((float)x, (float)y);
			
				Color p = Color::from(sample);

				buffers[0].write(x, y, p);
			}
		}
	}

	virtual void loadParams(ParameterLoader::GeneratorParameters& params) override
	{
		noise_ = FastNoiseFactory::create(getNoise(params, "noise"));
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
	FastNoise noise_;
};

#endif // FASTNOISE_GENERATOR_H