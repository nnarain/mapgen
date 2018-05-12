#ifndef GENERATOR_PIXEL_H
#define GENERATOR_PIXEL_H

#include <cstdint>

#include "utils/utils.h"

class Color
{
public:
	float r;
	float g;
	float b;
	float a;

    Color(float r, float g, float b, float a) :
        r(r), g(g), b(b), a(a)
    {

    }

	Color(float r, float g, float b) : Color(r, g, b, 1)
	{
	}

	Color(float v) : Color(v,v,v)
	{
	}

	Color() : Color(0)
	{
	}


	static Color from(const Color& a, const Color& b, float t)
	{
		Color p;
		p.r = utils::lerp(a.r, b.r, t);
		p.g = utils::lerp(a.g, b.g, t);
		p.b = utils::lerp(a.b, b.b, t);
		p.a = utils::lerp(a.a, b.a, t);

		return p;
	}
};

#endif //