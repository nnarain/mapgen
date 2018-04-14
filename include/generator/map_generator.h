#ifndef GENERATOR_MAP_GENERATOR_H
#define GENERATOR_MAP_GENERATOR_H

#include <memory>
#include <string>
#include <vector>

class MapGenerator
{
public:
	using Ptr = std::unique_ptr<MapGenerator>;

	virtual void generate() = 0;
	virtual void loadParams() = 0;

	virtual std::string getName() const = 0;
	virtual std::vector<std::string> getLayerNames() const = 0;

};

#endif  // GENERATOR_MAP_GENERATOR_H