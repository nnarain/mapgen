#ifndef GENERATOR_MAP_GENERATOR_MANAGER_H
#define GENERATOR_MAP_GENERATOR_MANAGER_H

#include "generator/map_generator.h"
#include "generator/generator_buffer_proxy.h"

#include <array>
#include <chrono>
#include <vector>
#include <string>
#include <thread>

class MapGeneratorManager
{
public:
	using LayerList = std::vector<GeneratorBuffer>;
	using ProxyList = std::vector<GeneratorBufferProxy>;

	MapGeneratorManager(ParameterLoader::GeneratorParameters& parameter_map, int buffer_size) :
		layers_(),
		parameter_list_(parameter_map),
		current_layer(0),
		buffer_width_(buffer_size),
		buffer_height_(buffer_size),
		update_ready_(false)
	{

	}

	void generate()
	{

	}

	std::thread startWorker(int x, int y, int w, int h)
	{
		ProxyList proxies;

		for (auto& buffer : layers_)
		{
			proxies.emplace_back(buffer, x, y, w, h);
		}

		return std::thread();
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

	void setUpdateReady(bool ready)
	{
		update_ready_ = ready;
	}

	void setCurrentLayer(int select)
	{
		current_layer = select;
	}

	std::vector<std::string> getCurrentLayerNames() const
	{
		return std::vector<std::string>();
	}

private:
	LayerList layers_;
	ProxyList proxies_;

	ParameterLoader::GeneratorParameters& parameter_list_;

	int current_layer;
	int buffer_width_;
	int buffer_height_;

	volatile bool update_ready_;
};

#endif // GENERATOR_MAP_GENERATOR_MANAGER_H