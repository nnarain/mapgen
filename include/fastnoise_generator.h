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
	FastNoiseGenerator()
	{
	}

	virtual void generate(GeneratorBufferList& buffers) override
	{
		const auto width = buffers[0].getWidth();
		const auto height = buffers[0].getHeight();

		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y)
			{
				auto sample = noise_.GetNoise((float)x, (float)y);
			
				Pixel p = Pixel::from(sample);

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