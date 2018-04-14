#ifndef GENERATOR_MAP_GENERATOR_MANAGER_H
#define GENERATOR_MAP_GENERATOR_MANAGER_H

#include "generator/map_generator.h"

#include <vector>
#include <string>

class MapGeneratorManager
{
public:
	using GeneratorList = std::vector<MapGenerator::Ptr>;

	MapGeneratorManager(GeneratorList& list) :
		generators_(list),
		current_map_generator_(0),
		current_layer(0)
	{

	}

	const MapGenerator::Ptr& getCurrentMapGenerator() const
	{
		return generators_[current_map_generator_];
	}

	void setCurrentGenerator(int select)
	{
		current_map_generator_ = select;
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
	int current_map_generator_;
	int current_layer;
};

#endif // GENERATOR_MAP_GENERATOR_MANAGER_H