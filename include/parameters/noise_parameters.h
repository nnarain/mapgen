#ifndef PARAMETERS_NOISE_PARAMETERS_H
#define PARAMETERS_NOISE_PARAMETERS_H

#include <FastNoise.h>

struct NoiseParameters
{
	int noise_type;
	int interp_type;
	int fractal_type;

	int seed;
	int octaves;
	float frequency;
	float gain;
	float lacunarity;
	

	NoiseParameters() :
		noise_type(0),
		interp_type(2),
		fractal_type(0),
		seed(0),
		octaves(0), 
		frequency(0.01f), 
		gain(0),
		lacunarity(2.0f)
	{
	}
};

#endif  // PARAMETERS_NOISE_PARAMETERS_H