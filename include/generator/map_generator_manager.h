#ifndef GENERATOR_MAP_GENERATOR_MANAGER_H
#define GENERATOR_MAP_GENERATOR_MANAGER_H

#include "generator/map_generator.h"

#include <vector>
#include <string>

class MapGeneratorManager
{
public:
	using GeneratorList = std::vector<MapGenerator::Ptr>;
	using LayerList = std::vector<GeneratorBuffer>;

	MapGeneratorManager(GeneratorList& list, ParameterLoader::ParameterMap& parameter_map, int buffer_size) :
		generators_(list),
		layers_(),
		parameter_map_(parameter_map),
		current_map_generator_(0),
		current_layer(0),
		buffer_width_(buffer_size),
		buffer_height_(buffer_size),
		update_ready_(false)
	{
		setCurrentGenerator(current_map_generator_);
	}

	void generate()
	{
		// get the current generator
		auto& generator = generators_[current_map_generator_];

		if (generator)
		{
			// reload parameters
			generator->loadParams(parameter_map_[generator->getName()]);
			// generate
			generator->generate(layers_);
		}

		update_ready_ = true;
	}

	uint8_t* getBufferData()
	{
		update_ready_ = false;
		return layers_[current_layer].get();
	}

	bool isUpdateReady() const
	{
		return update_ready_;
	}

	const MapGenerator::Ptr& getCurrentMapGenerator() const
	{
		return generators_[current_map_generator_];
	}

	void setCurrentGenerator(int select)
	{
		current_map_generator_ = select;

		// allocate layers
		const auto num_layers = getCurrentLayerNames().size();
		layers_.clear();
		for (auto i = 0u; i < num_layers; ++i)
		{
			layers_.push_back(GeneratorBuffer(buffer_width_, buffer_height_));
		}
	}

	void setCurrentLayer(int select)
	{
		current_layer = select;
	}

	std::vector<std::string> getGeneratorNames() const
	{
		std::vector<std::string> names;
		for (const auto& generator : generators_)
		{
			names.push_back(generator->getName());
		}

		return names;
	}

	std::vector<std::string> getCurrentLayerNames() const
	{
		return generators_[current_map_generator_]->getLayerNames();
	}

private:
	GeneratorList& generators_;
	LayerList layers_;
	ParameterLoader::ParameterMap& parameter_map_;
	int current_map_generator_;
	int current_layer;
	int buffer_width_;
	int buffer_height_;

	bool update_ready_;
};

#endif // GENERATOR_MAP_GENERATOR_MANAGER_H