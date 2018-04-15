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
	TerrainGenerator()
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
				auto elevation = elevation_.GetNoise((float)x, (float)y);
				auto moisture = moisture_.GetNoise((float)x, (float)y);
				auto temperature = temperature_.GetNoise((float)x, (float)y);

				Pixel pe = Pixel::from(elevation);
				Pixel pm = Pixel::from(moisture);
				Pixel pt = Pixel::from(temperature);

				buffers[0].write(x, y, pe);
				buffers[1].write(x, y, pm);
				buffers[2].write(x, y, pt);
			}
		}
	}

	virtual void loadParams(ParameterLoader::GeneratorParameters& params) override
	{
		elevation_ = FastNoiseFactory::create(params["elevation"].param.noise);
		moisture_ = FastNoiseFactory::create(params["moisture"].param.noise);
		temperature_ = FastNoiseFactory::create(params["temperature"].param.noise);
	}

	virtual std::string getName() const
	{
		return "Terrain";
	}

	virtual std::vector<std::string> getLayerNames() const
	{
		return { "Elevation", "Moisture", "Temperature" };
	}
private:
	FastNoise elevation_;
	FastNoise moisture_;
	FastNoise temperature_;
};

#endif // TERRAIN_GENERATOR_H