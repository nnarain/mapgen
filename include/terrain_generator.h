#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include "generator/map_generator.h"
#include "parameters/parameter_loader.h"
#include "factory/fastnoise_factory.h"
#include "utils/utils.h"

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
				
				auto land_mask = (elevation > 0);

				Pixel pe = Pixel::from(elevation);
				Pixel pl = (land_mask) ? Pixel(183, 110, 0) : Pixel(41, 85, 244);

				buffers[0].write(x, y, pe);
				buffers[1].write(x, y, pl);
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
		return { "Elevation", "Land Mask" };
	}
private:
	FastNoise elevation_;
	FastNoise moisture_;
	FastNoise temperature_;
};

#endif // TERRAIN_GENERATOR_H