#ifndef GENERATOR_MAP_GENERATOR_H
#define GENERATOR_MAP_GENERATOR_H

#include <memory>
#include <string>

class MapGenerator
{
public:
	using Ptr = std::unique_ptr<MapGenerator>;


	virtual void generate()
	{

	}

	virtual void loadParams()
	{

	}

	virtual std::string getName() const
	{
		return std::string("map");
	}

private:
};

#endif  // GENERATOR_MAP_GENERATOR_H