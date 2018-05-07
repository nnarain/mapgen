#ifndef MOUNTAIN_GENERATOR_H
#define MOUNTAIN_GENERATOR_H

#include "generator/map_generator.h"
#include "parameters/parameter_loader.h"
#include "generator/color.h"
#include "generator/gradient.h"
#include "factory/fastnoise_factory.h"
#include "utils/utils.h"

#include <FastNoise.h>

#include <map>
#include <string>
#include <cmath>


class MountainGenerator : public MapGenerator
{
public:


	MountainGenerator()
	{

	}

	virtual void generate(GeneratorBufferList& buffers)
	{
		const auto startX = buffers[0].startX();
		const auto startY = buffers[0].startY();
		const auto endX = buffers[0].endX();
		const auto endY = buffers[0].endY();
		
		for (int x = startX; x < endX; ++x)
		{
			for (int y = startY; y < endY; ++y)
			{
				auto sampleX = (float)x / scale_ + (x_offset_ * scroll_speed_);
				auto sampleY = (float)y / scale_ + (y_offset_ * scroll_speed_);

				auto base = mountain_mask_.GetNoise(sampleX, sampleY);
				base = utils::range(base, -1.f, 1.f, 0.f, 1.f);

				auto b = Color::from(Color(0), Color(1), base);

				Color m;

				if (base > threshold_)
				{
					m = Color(1);
				}
				else
				{
					m = Color(0);
				}

				buffers[0].write(x, y, b);
				buffers[1].write(x, y, m);
			}
		}

	}
	
	virtual void loadParams(ParameterLoader::GeneratorParameters& params) override
	{
		mountain_mask_ = FastNoiseFactory::create(getNoise(params, "mountain_mask"));
		mountain_lookup_ = FastNoiseFactory::create(getNoise(params, "mountain_lookup"));

		mountain_mask_.SetCellularNoiseLookup(&mountain_lookup_);

		threshold_ = getFloat(params, "threshold");
		x_offset_ = getFloat(params, "x_offset");
		y_offset_ = getFloat(params, "y_offset");
		scroll_speed_ = getFloat(params, "scroll_speed");
		scale_ = getFloat(params, "scale");
	}

	virtual std::string getName() const
	{
		return "Mountain";
	}

	virtual std::vector<std::string> getLayerNames() const
	{
		return { "Base", "Mask" };
	}
private:
	FastNoise mountain_mask_;
	FastNoise mountain_lookup_;

	float threshold_;
	float x_offset_;
	float y_offset_;
	float scroll_speed_;
	float scale_;
};

#endif // MOUNTAIN_GENERATOR_H