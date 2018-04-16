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

				Color pe = Color::from(elevation);
				
				Color pl;
				if (land_mask)
				{
					pl = Color::from(land_dark_, land_light_, elevation);
				}
				else 
				{
					pl = Color::from(water_light_, water_dark_, 1.f - elevation);
				}

				buffers[0].write(x, y, pe);
				buffers[1].write(x, y, pl);
			}
		}
	}

	virtual void loadParams(ParameterLoader::GeneratorParameters& params) override
	{
		elevation_ = FastNoiseFactory::create(getNoise(params, "elevation"));

		land_light_ = Color::from(getColor(params, "land_light"));
		land_dark_ = Color::from(getColor(params, "land_dark"));
		water_light_ = Color::from(getColor(params, "water_light"));
		water_dark_ = Color::from(getColor(params, "water_dark"));

		scale_ = getFloat(params, "scale");
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

	Color land_light_, land_dark_;
	Color water_light_, water_dark_;

	float scale_;
};

#endif // TERRAIN_GENERATOR_H