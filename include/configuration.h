#ifndef CONFIGURATION_H
#define CONFIGURATION_H

struct Configuration
{
	int seed;
	int octaves;
	float frequency;
	float gain;
	float lacunarity;

	Configuration() : 
		seed(0),
		octaves(0), 
		frequency(0.01f), 
		gain(0),
		lacunarity(2.0f)
	{
	}
};

#endif  // CONFIGURATION_H
