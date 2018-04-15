#include "parameters/parameter_loader.h"

#include <fstream>
#include <sstream>

ParameterLoader::ParameterLoader(const std::string& file) :
	noise_types_({ "value", "value_fractal", "perlin", "perlin_fractal", "simplex", "simplex_fractal",
		"cellular", "whitenoise", "cubic", "cubic_fractal" }),
	interp_types_({ "linear", "hermite", "quintic" }),
	fractal_types_({ "fbm", "billow", "rigidmulti" }),
	cellular_distance_function_({ "euclidean", "manhattan", "natural" }),
	cellular_return_type_({ "cellvalue", "noiselookup", "distance", "distance2", "distance2add", "distance2sub", "distance2mul", "distance2div" }),
	filename_(file)
{
	auto root = YAML::LoadFile(file);
	load(root);
}

std::map<std::string, ParameterLoader::GeneratorParameters>& ParameterLoader::getParams()
{
	return generator_params_;
}

void ParameterLoader::save()
{
	YAML::Emitter out;

	out << YAML::BeginMap;
	for (auto& it : generator_params_)
	{
		out << YAML::Key << it.first;
		out << YAML::Value;
		emitGeneratorParams(out, it.second);
	}
	out << YAML::EndMap;

	std::ofstream file(filename_);
	file << out.c_str();
}

void ParameterLoader::emitGeneratorParams(YAML::Emitter& out, GeneratorParameters& params)
{
	out << YAML::BeginMap;

	for (auto& it : params)
	{
		out << YAML::Key << it.first;

		auto param = it.second;

		if (param.type == ParameterValue::Type::Scalar)
		{
			out << YAML::Value << param.param.value;
		}
		else if (param.type == ParameterValue::Type::Noise)
		{
			out << YAML::Value;
			emitNoiseParameters(out, param.param.noise);
		}
		else if (param.type == ParameterValue::Type::Color)
		{
			out << YAML::Value;
			emitColor(out, &param.param.color[0]);
		}
	}

	out << YAML::EndMap;
}

void ParameterLoader::emitNoiseParameters(YAML::Emitter& out, NoiseParameters& params)
{
	out << YAML::BeginMap;
	out << YAML::Key << "noise_type" << YAML::Value << noise_types_[params.noise_type];
	out << YAML::Key << "fractal_type" << YAML::Value << fractal_types_[params.fractal_type];
	out << YAML::Key << "interp_type" << YAML::Value << interp_types_[params.interp_type];
	out << YAML::Key << "seed" << YAML::Value << params.seed;
	out << YAML::Key << "frequency" << YAML::Value << params.frequency;
	out << YAML::Key << "octaves" << YAML::Value << params.octaves;
	out << YAML::Key << "gain" << YAML::Value << params.gain;
	out << YAML::Key << "lacunarity" << YAML::Value << params.lacunarity;
	out << YAML::Key << "celluar_distance" << YAML::Value << cellular_distance_function_[params.cellular_distance_function];
	out << YAML::Key << "cellular_return" << YAML::Value << cellular_return_type_[params.cellular_return_type];
	out << YAML::Key << "cellular_jitter" << YAML::Value << params.cellular_jitter;
	out << YAML::EndMap;
}

void ParameterLoader::emitColor(YAML::Emitter& out, float* color)
{
	std::stringstream ss;
	ss << std::hex << ((int)(color[0] * 255.f)) << ((int)(color[1] * 255.f)) << ((int)(color[2] * 255.f)) << ((int)(color[3] * 255.f));

	out << YAML::BeginMap;
	out << YAML::Key << "color" << YAML::Value << ss.str();
	out << YAML::EndMap;
}


void ParameterLoader::load(YAML::Node& node)
{
	for (auto it = node.begin(); it != node.end(); ++it)
	{
		auto key = it->first.as<std::string>();
		auto params = loadGeneratorParams(it->second);

		generator_params_[key] = params;
	}
}

ParameterLoader::GeneratorParameters ParameterLoader::loadGeneratorParams(YAML::Node& node)
{
	GeneratorParameters params;

	for (auto it = node.begin(); it != node.end(); ++it)
	{
		auto key = it->first.as<std::string>();
		auto node = it->second;

		ParameterValue value;
		value.name = key;

		// check if the value is a float
		if (node.Type() == YAML::NodeType::Scalar)
		{

			value.type = ParameterValue::Type::Scalar;
			value.param.value = node.as<float>();

			params[key] = value;
		}
		else if (node.Type() == YAML::NodeType::Map)
		{
			// if it contains a noise_type field, it is a noise parameter
			if (node["noise_type"])
			{
				auto noise_params = loadNoiseParameter(node);

				value.type = ParameterValue::Type::Noise;
				value.param.noise = noise_params;

				params[key] = value;
			}
			// if it contains a color field it is a color parameter
			else if (node["color"])
			{
				value.type = ParameterValue::Type::Color;
				loadColorParameter(node["color"], &value.param.color[0]);
				params[key] = value;
			}
		}
	}

	return params;
}

void ParameterLoader::loadColorParameter(YAML::Node& node, float* color)
{
	auto hexstr = node.as<std::string>();

	std::stringstream ss;
	ss << std::hex << hexstr;

	uint32_t hexint;
	ss >> hexint;

	color[0] = ((float)((hexint & 0xFF000000) >> 24) / 255.f);
	color[1] = ((float)((hexint & 0x00FF0000) >> 16) / 255.f);
	color[2] = ((float)((hexint & 0x0000FF00) >> 8) / 255.f);
	color[3] = ((float)((hexint & 0x000000FF) >> 0) / 255.f);
}

NoiseParameters ParameterLoader::loadNoiseParameter(YAML::Node& node)
{
	NoiseParameters params;

	// find the noise type
	auto noise_type = node["noise_type"].as<std::string>();
	params.noise_type = findIndex(noise_types_, noise_type);

	// find interp type
	if (node["interp_type"])
	{
		auto interp_type = node["interp_type"].as<std::string>();
		params.interp_type = findIndex(interp_types_, interp_type);
	}

	// find fractal type
	if (node["fractal_type"])
	{
		auto fractal_type = node["fractal_type"].as<std::string>();
		params.fractal_type = findIndex(fractal_types_, fractal_type);
	}

	if (node["cellular_distance"])
	{
		auto cellular_distane_function = node["cellular_distance"].as<std::string>();
		params.cellular_distance_function = findIndex(cellular_distance_function_, cellular_distane_function);
	}

	if (node["cellular_return"])
	{
		auto cellular_return = node["cellular_return"].as<std::string>();
		params.cellular_return_type = findIndex(cellular_return_type_, cellular_return);
	}

	quickLoad(node, "seed", params.seed);
	quickLoad(node, "octaves", params.octaves);
	quickLoad(node, "frequency", params.frequency);
	quickLoad(node, "gain", params.gain);
	quickLoad(node, "lacunarity", params.lacunarity);
	quickLoad(node, "cellular_jitter", params.cellular_jitter);

	return params;
}