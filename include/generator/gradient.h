#ifndef GENERATOR_GRADIENT_H
#define GENERATOR_GRADIENT_H

#include "generator/color.h"


class Gradient
{
public:
	Gradient(Color a, Color b) :
		a_(a),
		b_(b)
	{
	}

	Color get(float t)
	{
		return Color::from(a_, b_, t);
	}

private:
	Color a_;
	Color b_;
};

#endif // GENERATOR_GRADIENT_H