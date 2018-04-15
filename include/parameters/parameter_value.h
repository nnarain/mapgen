#ifndef PARAMETERS_PARAMETER_VALUE_H
#define PARAMETERS_PARAMETER_VALUE_H

#include "parameters/noise_parameters.h"

#include <string>
#include <cstdint>

struct ParameterValue
{
	enum class Type
	{
		Scalar,
		Noise,
		Color
	};

	union Parameter
	{
		float value;
		NoiseParameters noise;
		float color[4];
	};

	Type type;
	Parameter param;
	std::string name;

	ParameterValue() : type{Type::Scalar}, param { 0.1f }
	{

	}
};

#endif // PARAMETERS_PARAMETER_VALUE_H