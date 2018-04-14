#ifndef PARAMETERS_PARAMETER_VALUE_H
#define PARAMETERS_PARAMETER_VALUE_H

#include "parameters/noise_parameters.h"

#include <string>

struct ParameterValue
{
	enum class Type
	{
		Scalar,
		Noise
	};

	union Parameter
	{
		float value;
		NoiseParameters noise;
	};

	Type type;
	Parameter param;
	std::string name;

	ParameterValue() : type{Type::Scalar}, param { 0.1f }
	{

	}
};

#endif // PARAMETERS_PARAMETER_VALUE_H