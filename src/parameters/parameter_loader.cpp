#include "parameters/parameter_loader.h"

#include <fstream>

ParameterLoader::ParameterLoader(const std::string& file) : 
	noise_types_({"value", "value_fractal", "perlin", "perlin_fractal", "simplex", "simplex_fractal",
		"cellular", "whitenoise", "cubic", "cubic_fractal"}),
	interp_types_({"linear", "hermite", "quintic"}),
	fractal_types_({"fbm", "billow", "rigidmulti"}),
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

		// check if the value is a float
		if (node.Type() == YAML::NodeType::Scalar)
		{
			ParameterValue value;
			value.name = key;
			value.type = ParameterValue::Type::Scalar;
			value.param.value = node.as<float>();

			params[key] = value;
		}
		else if (node.Type() == YAML::NodeType::Map)
		{
			if (node["noise_type"])
			{
				auto noise_params = loadNoiseParameter(node);

				ParameterValue value;
				value.name = key;
				value.type = ParameterValue::Type::Noise;
				value.param.noise = noise_params;

				params[key] = value;
			}
		}
	}

	return params;
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

	quickLoad(node, "seed", params.seed);
	quickLoad(node, "octaves", params.octaves);
	quickLoad(node, "frequency", params.frequency);
	quickLoad(node, "gain", params.gain);
	quickLoad(node, "lacunarity", params.lacunarity);

	return params;
}