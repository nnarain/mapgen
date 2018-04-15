#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include "generator/map_generator.h"
#include "parameters/parameter_loader.h"
#include "factory/fastnoise_factory.h"

#include <FastNoise.h>

#include <map>
#include <string>


class TerrainGenerator : public MapGenerator
{
public:
	TerrainGenerator(std::map<std::string, ParameterLoader::GeneratorParameters>& params) :
		params_(params[getName()])
	{

	}

	virtual void generate(GeneratorBufferList& buffers)
	{
		const auto width = buffers[0].getWidth();
		const auto height = buffers[0].getHeight();

		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y)
			{
				auto sample = noise_.GetNoise(x, y);

				Pixel p;
				p.r = (uint8_t)(sample * 255.0f);
				p.g = (uint8_t)(sample * 255.0f);
				p.b = (uint8_t)(sample * 255.0f);

				buffers[0].write(x, y, p);
			}
		}
	}

	virtual void loadParams()
	{
		noise_ = FastNoiseFactory::create(params_["noise"].param.noise);
	}

	virtual std::string getName() const
	{
		return "Terrain";
	}

	virtual std::vector<std::string> getLayerNames() const
	{
		return { "Height" };
	}
private:
	ParameterLoader::GeneratorParameters& params_;
	FastNoise noise_;
};

#endif // TERRAIN_GENERATOR_H