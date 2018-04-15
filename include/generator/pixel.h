#ifndef GENERATOR_PIXEL_H
#define GENERATOR_PIXEL_H

#include <cstdint>

class Pixel
{
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	Pixel(uint8_t r, uint8_t g, uint8_t b) :
		r(r), g(g), b(b), a(255)
	{
	}

	Pixel(uint8_t v) : Pixel(v,v,v)
	{
	}

	Pixel() : Pixel(0)
	{
	}

	/**
		Expects sample to be in range [0,1]
	*/
	static Pixel from(float sample)
	{
		return Pixel((uint8_t)(sample * 255.0f));
	}
};

#endif //