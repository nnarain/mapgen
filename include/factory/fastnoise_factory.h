#ifndef FASTNOISE_FACTORY_H
#define FASTNOISE_FACTORY_H

#include <FastNoise.h>
#include "parameters/noise_parameters.h"

class FastNoiseFactory
{
public:
	static FastNoise create(const NoiseParameters& params)
	{
		FastNoise noise;
		noise.SetNoiseType(static_cast<FastNoise::NoiseType>(params.noise_type));
		noise.SetFractalType(static_cast<FastNoise::FractalType>(params.fractal_type));
		noise.SetInterp(static_cast<FastNoise::Interp>(params.interp_type));
		noise.SetSeed(params.seed);
		noise.SetFrequency(params.frequency);
		noise.SetFractalOctaves(params.octaves);
		noise.SetFractalGain(params.gain);
		noise.SetFractalLacunarity(params.lacunarity);
		noise.SetCellularDistanceFunction(static_cast<FastNoise::CellularDistanceFunction>(params.cellular_distance_function));
		noise.SetCellularReturnType(static_cast<FastNoise::CellularReturnType>(params.cellular_return_type));
		noise.SetCellularJitter(params.cellular_jitter);

		return noise;
	}
};

#endif // FASTNOISE_FACTORY_H