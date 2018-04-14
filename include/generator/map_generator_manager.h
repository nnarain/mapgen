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
		generators_(list)
	{

	}

	void setCurrentGenerator(int select)
	{

	}

	void selectCurrentLayer(int select)
	{

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

private:
	GeneratorList& generators_;
};

#endif // GENERATOR_MAP_GENERATOR_MANAGER_H